#include <node.h>
#include <v8.h>

// 实际方法
static void Method(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::String::NewFromUtf8(
        isolate, "world", v8::NewStringType::kNormal).ToLocalChecked());
}

static void FakeInit(const v8::FunctionCallbackInfo<v8::Value>& args) {
  auto isolate = args.GetIsolate();
  auto exception = v8::Exception::Error(v8::String::NewFromUtf8(isolate,
      "FakeInit should never run!", v8::NewStringType::kNormal)
          .ToLocalChecked());
  isolate->ThrowException(exception);
}

// 上下文感知宏
// 以c 语言的规则去翻译
extern "C" NODE_MODULE_EXPORT void
NODE_MODULE_INITIALIZER(v8::Local<v8::Object> exports,
                        v8::Local<v8::Value> module,
                        v8::Local<v8::Context> context) {
  NODE_SET_METHOD(exports, "hello", Method);
  
  NODE_SET_METHOD(exports, "fake", FakeInit);
}


// Define a Node.js module, but with the wrong version. Node.js should still be
// able to load this module, multiple times even, because it exposes the
// specially named initializer above.
#undef NODE_MODULE_VERSION
#define NODE_MODULE_VERSION 3
NODE_MODULE(NODE_GYP_MODULE_NAME, FakeInit)


/*******************************************************************************/

// #include <node.h>
// #include <v8.h>

// // 作用相当于：module.exports.hello = () => 'world';
// namespace demo
// {
// using v8::FunctionCallbackInfo;
// using v8::Isolate;
// using v8::Local;
// using v8::NewStringType;
// using v8::Object;
// using v8::String;
// using v8::Value;

// void Method(const FunctionCallbakInfo<Value> &args)
// {
//     // 形参中的& 表示引用传递、即形参是实参的别名
//     // 与指针传递还是不一样的吧：会不会拷贝一份指针的问题
//     // & 用在定义时表示引用；在变量操作时表示取地址

//     Isolate *isolate = args.GetIsolate();
//     args.GetReturnValue().Set(
//         String::NewFromUtf8(isolate, "world", NewStringType::kNormal).ToLocalChecked());
// }

// /**
//  * 导出函数名hello
//  * 导出函数体Method (应该也可以命名为其他吧)
// */

// // 所有Node.js 插件都必须导出如下初始化函数
// void Initialize(Local<Object> exports)
// {
//     NODE_SET_METHOD(exports, "hello", Method);
// }
// // 初始宏
// NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

// } // namespace demo