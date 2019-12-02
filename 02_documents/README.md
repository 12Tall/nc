# C++ 扩展  

`Node.js`扩展是指动态链接的共享对象(在win下和动态链接库类似),通过`C++`开发，可以使用[require()](https://nodejs.org/api/modules.html#modules_require_id)函数加载至`Node.js`，作为一般模块使用。主要用来提供JavaScript与C/C++库的接口。  

实现扩展的方法有三种：`N-API`，`nan`或者直接使用内置的`v8`、`libuv`以及`Node.js`库。除非需要直接访问`N-API`没有提供的功能，否则`N-API`是不二之选。更多关于`N-API`的信息请参考[N-API实现C/C++扩展](https://nodejs.org/api/n-api.html)。    

在不使用`N-API` 的情况下，实现扩展需要掌握许多`Node.js`组件和API知识，比较复杂。  

- V8：`Node.js`目前提供实现JavaScript的C++库。V8提供了创建对象、函数调用等机制。V8引擎的API主要记录在`v8.h`头文件(`deps/v8/include/v8.h`，`Node.js`源码树)中，也可以[在线查阅](https://v8docs.nodesource.com/)。  
- [libuv](https://github.com/libuv/libuv)：实现`Node.js`事件循环、`worker`线程及其所有异步行为的`C`库。同时它也是一个跨平台的抽象库，提供了简单的、跨主流操作系统的系统任务调用，例如：文件系统、Sockets、定时器以及系统事件。libuv同时提供了一种`类pthreads`的线程抽象，可用于驱动需要超越标准事件循环的更复杂的异步扩展。开发者需要思考在各类耗时任务中如何利用非阻塞系统操作、worker线程或libuv线程避免消息循环阻塞。  
- 内部`Node.js`库。`Node.js`自身可被扩展调用的API。最重要的是`node::ObjectWrap`类。  
- `Node.js`包含其他静态链接库，例如OpenSSL。这些静态链接库在`deps/`目录下。只有libuv、OpenSSL、v8和zlib符号会被`Node.js`有目的的导出，以便扩展使用。更多信息参见[Node.js的依赖项](https://nodejs.org/api/addons.html#addons_linking_to_node_js_own_dependencies)。  

以下所有示例提供[下载](https://github.com/nodejs/node-addon-examples)并可作为学习扩展的出发点。  
*注：例子可能有些过时，最好去链接下载最新的运行*  

## Hello World  

`Hello World`是最简单的扩展示例，通过C++实现，等效于下面JavaScript代码：  

```javascript
module.exports.hello = ()=> 'world';
```

首先创建`hello.cc`：  

```c++
// hello.cc 已编译通过
#include <node.h>

namespace demo
{
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Value;

// 正常的C++ 函数，名字可以任意取
void Method(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate(); // 获取v8 虚拟机实例

    args.GetReturnValue() // 获取返回值实例
        .Set(String::NewFromUtf8(
                 isolate,
                 "world",
                 NewStringType::kNormal)
                 .ToLocalChecked());
}

void Initialize(Local<Object> exports)
{
    NODE_SET_METHOD(exports, // 导出对象
                    "hello", // 导出方法名
                    Method); // 实际函数名
}

NODE_MODULE(NODE_GYO_MODULE_NAME, Initialize)

} // namespace demo
```  

所有的`Node.js` 扩展都必须按下面模式导出一个初始化函数：  

```c++
void Initialize(Local<Object> exports);
NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
```  

`NODE_MODULE` 没有分号，表示一个宏命令(`v8.h`)而不是函数。  
`module_name` 必须与文件名保持一致(不包含`.node`后缀)。  
在`hello.cc`例子中，初始化函数时`Initialize`扩展模块名是`addon`。  
当使用`node-gyp`构建扩展时，会通过使用宏`NODE_GYP_MODULE_NAME`作为`NODE_MODULE()`的第一个参数，来确保最终的二进制文件传递给`NODE_MODULE()`  
*注：验证直接修改`NODE_GYP_MODULE_NAME`为字符串的操作并不能通过编译*  

## 上下文感知插件  

在某些环境中，可能需要在多个上下文中加载`Node.js`扩展。例如[Electron](https://electronjs.org/)会在运行时在一个进程中启动多个`Node.js`实例。每个实例都有自己的`require()`缓存，因此每个实例在`require()`加载时都需要一个本地扩展才能正确运行。从插件的角度来看，则必须支持被多次初始化。  


上下文感知扩展可以通过`NODE_MODULE_INITIALIZER`宏来构建，该宏命令将函数名扩展为`Node.js`在加载扩展时查找的函数名。因此，扩展可以采用下面的方法进行初始化。  

```c++
// 代码片段
using namespace v8;

extern "C" NODE_MODULE_EXPORT void

NODE_MODULE_INITIALIZER(Loacal<Object> exports,
                        Local<Value> module,
                        Local<COntext> context)
{
    /*初始化步骤*/
}
```  

第二种选择是采用`NODE_MODULE_INIT()`宏来构建上下文感知扩展。与`NODE_MODULE()`不同的是`NODE_MODULE()`需要预先给定一个初始化函数，而`NODE_MODULE_INIT()`后跟函数体初党初始化的声明。  

下面三个变量在`NODE_MODULE_INIT()`函数体中可能会用到：  

- `Loacal<Object> exports`  
- `Local<Value> module`  
- `Local<COntext> context`  

构建上下文感知插件，就要多注意管理全局静态数据。因为插件可能会在不同的线程中被加载许多次。插件中任何全局静态的数据都应该被可靠的保护。并且不要包含对JavaScript对象的持久引用。因为JavaScript对象只在一个上下文中有效，当上下文切换时可能会因为引用错误导致程序崩溃。  

上下文感知插件可以通过下面步骤构建来规避全局静态数据：  

- 定义一个类保存每个实例的数据。这个类包含一个`v8::Persistent<v8::Object>`对`expots`对象添加弱引用。与弱引用关联的回调函数将自动销毁该类的实例。  
- 在插件初始化时构造此类的实例，以便将`v8::Persistent<v8::Object>`设置为`exports`对象。  
- 保存此类的实例在`v8::External`，通过`v8::External`传递给`v8::FunctionTemplate`创建JavaScript原生函数的构造函数，并将其暴露给JavaScript的所有方法。`v8::FunctionTemplate` 构造函数接受的第三个参数为`v8::External`。  

这将确保每个插件实例的数据能被JavaScript调用。每个插件实例的数据必须传递到插件可能创建的异步回调中。  
下面例子展示了上下文感知插件的实现：  

```c++
/**
 * 像是C++ 函数数据的持久化存储一样
*/
#include <node.h>

using namespace v8;

class AddonData
{
    // 构造函数
public:
    // 构造函数后跟冒号主要用于数据初始化：
    // 1. 初始化const成员
    // 2. 初始化引用成员
    // 3. 调用父类构造函数
    // 4. 调用成员类的构造函数
    AddonData(Isolate *isolate, Local<Object> exports) : call_count(0)
    {
        // 将此实例与导出联系起来
        exports_.Reset(isolate, exports);
        exports_.SetWeak(this, DeleteMe, WeakCallbackType::kParameter);
    }

    ~AddonData()
    {
        if (!exports_.IsEmpty())
        {
            // 重置引用，以避免数据泄露
            exports_.ClearWeak();
            exports_.Reset();
        }
    }

    // 实例数据
    int call_count;

private:
    // 导出接口调用，垃圾回收方法
    static void DeleteMe(const WeakCallbackInfo<AddonData> &info)
    {
        delete info.GetParameter();
    }

    // 声明持久化引用对象
    v8::Persistent<v8::Object> exports_;
}; // 类的声明后面要跟分号？

static void Method(const v8::FunctionCallbackInfo<v8::Value> &info)
{
    // 检索每个加载项实例数据
    AddonData *data =
        // reinterpret_cast():重新解释比特位
        reinterpret_cast<AddonData *>(info.Data().As<External>()->Value());
    data->call_count++;
    info.GetReturnValue().Set((double)data->call_count);
}

// 初始化上下文感知插件
NODE_MODULE_INIT(/* exports, module, context */)
{
    Isolate *isolate = context->GetIsolate();

    // 为上下文实例创建数据实例
    AddonData *data = new AddonData(isolate, exports);
    // 将数据封装在v8::External 以便我们可以将其传递给我们公开的方法。
    Local<External> external = External::New(isolate, data);

    // 暴露"Method"方法给JavaScript, 并将我们上面构建的v8::External 传递给FunctionTemplate
    // 以确保JavaScript 能够收到数据
    exports->Set(context, // 上下文
                 String::NewFromUtf8(isolate, "method", NewStringType::kNormal)
                     .ToLocalChecked(), // 方法名
                 FunctionTemplate::New(isolate, Method, external)
                     ->GetFunction(context)
                     .ToLocalChecked()) // 数据
        .FromJust();
}
```

*注：插件的函数可能需要之前的状态，这样就需要在每个`Node.js`实例中，有一个全局变量保存之前的状态*  
*但是又需要避免内存泄漏，所以才这么复杂吧*  

## Worker支持  
为了可以被多个`Node.js`环境加载，例如一个主线程与工作线程，一个插件应该被定义为：  

- `N-API` 插件  
- 或者通过`NODE_MODULE_INIT()`声明为上下文感知插件  

为了支持[工作线程](https://nodejs.org/api/worker_threads.html#worker_threads_class_worker)，插件需要通过`AddEnvironmentCleanupHook()`清除任何线程中可能会用到的资源。  

```c++
void AddEnvironmentCleanupHook( v8::Isolate* isolate,
                                void (*fun)(void* arg),
                                void* arg);
```  

下面是`addon.cc`使用`AddEnvironmentCleanupHook()`的实例：  

```c++
// 看不大懂。。。。
// addon.cc
#include <assert.h>
#include <stdlib.h>
#include <node.h>

using node::AddEnvironmentCleanupHook;
using v8::HandleScope;
using v8::Isolate;
using v8::Local;
using v8::Object;

// 在实际应用中，不要依赖静态/全局数据
static char cookie[] = "yum yum";
static int cleanup_cb1_called = 0;
static int cleanup_cb2_called = 0;

static void cleanup_cb1(void *arg)
{
    // 类似于reinterpret_cast
    Isolate *isolate = static_cast<Isolate *>(arg);
    HandleScope scope(isolate);
    Local<Object> obj = Object::New(isolate);
    assert(!obj.IsEmpty());
    assert(obj->IsObject());
    cleanup_cb1_called++;
}

static void cleanup_cb2(void *arg)
{
    assert(arg == static_cast<void *>(cookie));
    cleanup_cb2_called++;
}

static void sanity_check(void *)
{
    assert(cleanup_cb1_called == 1);
    assert(cleanup_cb2_called == 1);
}

NODE_MODULE_INIT()
{
    Isolate *isolate = context->GetIsolate();

    AddEnvironmentCleanupHook(isolate, sanity_check, nullptr);
    AddEnvironmentCleanupHook(isolate, cleanup_cb2, cookie);
    AddEnvironmentCleanupHook(isolate, cleanup_cb1, isolate);
}
```  

通过下列命令测试：  

```javascript
// test.js
require('./build/Release/addon');
```  

## 构建  

源码编写完成后，必须要编译成二进制文件`addon.node`。于是，我们需要创建一个`bionding.gyp`指导文件，在项目根目录下，指导文件采用类似于`JSON`的数据格式，可以被[node-gyp](https://github.com/nodejs/node-gyp)用于指导编译。  

```json
{
  "targets": [  // 别漏掉s
    {
      "target_name": "addon",
      "sources": [ "hello.cc" ]  // 别漏掉s
    }
  ]
}
```  

`nod-gyp`的版本作为`npm`的一部分同`Node.js`绑定、分发。此版本不直接提供给开发者使用，仅用于支持`npm install`命令编译和安装插件。开发者可以使用`npm install -g node-gyp` 直接使用`node-gyp`。更多信息请参考[`node-gyp`安装指导](https://github.com/nodejs/node-gyp#installation)，也包括一些平台相关的信息。  

一旦`binding.gyp`创建完成，就可以使用`node-gyp configure`来生成项目文件(build/目录下)：对于`*nix`会生成`makefile`；而对于Windows 会生成`vcxproj`文件。  
随后，可以通过`node-gyp build`编译生成`addon.node`。一般会被生成在`build/Release/`目录下。  
在使用`npm install`命令时，npm会使用绑定的`node-gyp`版本执行上面的步骤，来编译插件。编译成功后，Node.js就可以通过[require()](https://nodejs.org/api/modules.html#modules_require_id)加载二进制文件`*.node`。  

```javascript
// hello.js
const addon = require('./build/Release/addon');

console.log(addon.hello());
// Prints: 'world'
```

因为目标文件的路径依赖于编译条件(可能会被编译成Debug版本)，插件可以使用[bindings](https://github.com/TooTallNate/node-bindings)包来加载编译模块。  

`bindings`包的实现与`try...catch`类似：  

```javascript
try {
  return require('./build/Release/addon.node');
} catch (err) {
  return require('./build/Debug/addon.node');
}
```  

## 连接Node.js自身依赖项  

Node.js使用静态链接库，例如：v8、libuv和OpenSSL。所有的插件都需要链接v8，有些还需要其他的依赖项。一般来说，就是用`#include<...>`就行了，`node-gyp`会自动定位到头文件。然而也有些坑需要注意下：  

- 当`node-gyp`运行时会检测Node.js的发行版本并下载完整源码或者头文件。如果下载了完整源码，那插件将具有完整的Node.js依赖项访问权限；如果只下载了头文件，则只有Node.js导出的符号可用。  
- 可以使用`--nodedir`来指定本地Node.js源映像。使用此项，插件将有权访问所有依赖项。  

## 使用require()加载插件  

插件的扩展名为`.node`(其实格式同dll或so)。`require()`方法就是查找`.node`文件并初始化这个动态链接库。  
`reuqire()`在加载文件时如果不指定后缀名的话会优先查找加载`.js`而不是`.node`。  

## Node.js的本地抽象  

本文中的示例均直接采用`Node.js`和v8 api来实现插件。v8的api可能会随着v8引擎的版本更新。Node.js的版本尽量减少更新的频率，却难以保证v8 api的稳定性。  

`nana`([Node.js本地抽象](https://github.com/nodejs/nan))提供了一系列工具来保证插件的兼容性。查看`nana`[示例](https://github.com/nodejs/nan/tree/master/examples/)  


