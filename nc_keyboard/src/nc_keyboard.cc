#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include "keyboard_win.h"

using namespace v8;
using namespace std;

// 模拟连续按键
static void typeVirtualKey(const FunctionCallbackInfo<Value> &args)
{
    int len = args.Length();
    Isolate *isolate = args.GetIsolate();
    for (int i = 0; i < len; i++)
    {
        if (args[i]->IsNumber())
        {
            Local<Number> num = Local<Number>::Cast(args[i]);
            WORD keyCode = num->Int32Value() & 0xff;
            SendKey(keyCode);
        }
    }

    args.GetReturnValue().SetUndefined();
}

// 模拟按下
static void keyDown(const FunctionCallbackInfo<Value> &args)
{
    int len = args.Length();
    Isolate *isolate = args.GetIsolate();
    if (args[0]->IsNumber())
    {
        Local<Number> num = Local<Number>::Cast(args[0]);
        WORD keyCode = num->Int32Value() & 0xff;
        KeyDown(keyCode);
    }

    args.GetReturnValue().SetUndefined();
}

// 模拟弹起
static void keyUp(const FunctionCallbackInfo<Value> &args)
{
    int len = args.Length();
    Isolate *isolate = args.GetIsolate();
    if (args[0]->IsNumber())
    {
        Local<Number> num = Local<Number>::Cast(args[0]);
        WORD keyCode = num->Int32Value() & 0xff;
        KeyUp(keyCode);
    }

    args.GetReturnValue().SetUndefined();
}

extern "C" NODE_MODULE_EXPORT void

NODE_MODULE_INITIALIZER(Local<Object> exports,
                        Local<Value> modules,
                        Local<Context> context)
{
    NODE_SET_METHOD(exports, "typeVirtualKey", typeVirtualKey);
    NODE_SET_METHOD(exports, "keyDown", keyDown);
    NODE_SET_METHOD(exports, "keyUp", keyUp);
}