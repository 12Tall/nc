

#include <node.h>
#include <v8.h>
#include <Windows.h>
#include <winuser.h>
#include <string>

using namespace v8;

void SendUnicode(wchar_t data)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = 0;
    input[0].ki.wScan = data;
    input[0].ki.dwFlags = 0x4; //KEYEVENTF_UNICODE;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = 0;
    input[1].ki.wScan = data;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4; //KEYEVENTF_UNICODE;

    SendInput(2, input, sizeof(INPUT));
}

static void MoveMouse(const FunctionCallbackInfo<Value> &args)
{
    setlocale(LC_ALL, "");
    Isolate *isolate = args.GetIsolate();
    SendUnicode(L'二.');
    args.GetReturnValue().SetUndefined();
}

extern "C" NODE_MODULE_EXPORT void

NODE_MODULE_INITIALIZER(Local<Object> exports,
                        Local<Value> modules,
                        Local<Context> context)
{
    NODE_SET_METHOD(exports, "moveMouse", MoveMouse);
}