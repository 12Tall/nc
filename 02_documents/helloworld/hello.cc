// hello.cc
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