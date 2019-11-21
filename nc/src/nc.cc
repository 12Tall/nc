

#include <node.h>
#include <v8.h>
#include <windows.h>
#include <winuser.h>

using namespace v8;
using namespace std;

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

#pragma optimize("", off)
static void MoveMouse(const FunctionCallbackInfo<Value> &args)
{
    setlocale(LC_ALL, "");
    Isolate *isolate = args.GetIsolate();
    Local<Array> input = Local<Array>::Cast(args[0]);
    Local<Value> arg = args[0];

    if (arg->IsString())
    {
        Local<String> ss = arg->ToString();
        String::Utf8Value value(ss);
        string cc = string(*value);

        int iSize;
        wchar_t *pwszUnicode;

        //返回接受字符串所需缓冲区的大小，已经包含字符结尾符'\0'
        iSize = MultiByteToWideChar(CP_UTF8, 0, cc.c_str(), -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
        pwszUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));          //不需要 pwszUnicode = (wchar_t *)malloc((iSize+1)*sizeof(wchar_t))
        MultiByteToWideChar(CP_UTF8, 0, cc.c_str(), -1, pwszUnicode, iSize);

        SendUnicode(*pwszUnicode++);
        SendUnicode(*pwszUnicode++);
        SendUnicode(*pwszUnicode++);
        SendUnicode(*pwszUnicode++);
        SendUnicode(*pwszUnicode++);
        SendUnicode(*pwszUnicode++);
        SendUnicode(*pwszUnicode++);
        SendUnicode(*pwszUnicode++);
    }

    args.GetReturnValue().SetUndefined();
}

#pragma optimize("", on)
extern "C" NODE_MODULE_EXPORT void

NODE_MODULE_INITIALIZER(Local<Object> exports,
                        Local<Value> modules,
                        Local<Context> context)
{
    NODE_SET_METHOD(exports, "moveMouse", MoveMouse);
}