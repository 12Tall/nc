# 示例插件  

下面是一些基于v8 api的示例来帮助开发者上手。，请参阅在线[v8参考](https://v8docs.nodesource.com/)理解v8调用，[Emberdder's Guide](https://github.com/v8/v8/wiki/Embedder's%20Guide)，了解一些关于句柄、范围、函数模板的概念。  

每个例子都采用下面的`binding.gyp`文件：  

```json
{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc" ]
    }
  ]
}
```  

如果源文件多于一个，则在`sources`数组中添加：  

```json
"sources": ["addon.cc", "myexample.cc"]
```  

构建的命令就是：  

```bash
>$ node-gyp configure build
```  

## 函数参数  

插件通常会暴露对象或方法给Node.js调用。所以输入/输出参数必须要与C/C++代码存在映射关系。  

下面例子展示了如何读取JavaScript传入的参数并返回结果：  

```c++
#include <node.h>

namespace demo
{
using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void Add(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    // 数量异常
    if (args.Length() < 2)
    {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate,
                                "Wrong number of arguments",
                                NewStringType::kNormal)
                .ToLocalChecked()));
        return;
    }

    // 类型异常
    if (!args[0]->IsNumber() || !args[1]->IsNumber())
    {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate,
                                "Wrong arguments",
                                NewStringType::kNormal)
                .ToLocalChecked()));
        return;
    }

    // 加法运算
    // 拆箱
    double value =
        args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
    // 装箱
    Local<Number> num = Number::New(isolate, value);

    // 设置返回值(using the passed in
    // FunctionCallbackInfo<Value>&)
    args.GetReturnValue().Set(num);
}

void Init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

} // namespace demo
```  

编译完成后，可以在Node.js中调用：  

```js
// test.js
const addon = require('./build/Release/addon');

console.log('This should be eight:', addon.add(3, 5));
```