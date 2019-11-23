#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include "keyboard_win.h"

using namespace v8;
using namespace std;

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

extern "C" NODE_MODULE_EXPORT void

NODE_MODULE_INITIALIZER(Local<Object> exports,
                        Local<Value> modules,
                        Local<Context> context)
{
    NODE_SET_METHOD(exports, "typeVirtualKey", typeVirtualKey);
}