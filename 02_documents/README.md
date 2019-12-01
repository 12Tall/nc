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
