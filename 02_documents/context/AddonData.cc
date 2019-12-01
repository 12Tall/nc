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