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