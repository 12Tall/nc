#include <node.h>
#include <v8.h>
#include <windows.h>

using namespace v8;

static void MoveMouse(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    mouse_event(MOUSEEVENTF_LEFTDOWN, 100, 100, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 100, 100, 0, 0);
    // SetCursorPos(100, 100);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    args.GetReturnValue().SetUndefined();
}

extern "C" NODE_MODULE_EXPORT void

NODE_MODULE_INITIALIZER(Local<Object> exports,
                        Local<Value> modules,
                        Local<Context> context)
{
    NODE_SET_METHOD(exports, "moveMouse", MoveMouse);
}