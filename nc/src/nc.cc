

#include <node.h>
#include <v8.h>
#include <windows.h>
#include <winuser.h>
#include <cstdlib>

using namespace v8;
using namespace std;

void SendAscii(wchar_t data, BOOL shift)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));

    if (shift)
    {
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_SHIFT;
        SendInput(1, input, sizeof(INPUT));
    }

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = data;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = data;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));

    if (shift)
    {
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_SHIFT;
        input[0].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, input, sizeof(INPUT));
    }
}

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

// 关闭调试时优化
#pragma optimize("", off)
static void typeUnicode(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
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
        pwszUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));         //不需要 pwszUnicode = (wchar_t *)malloc((iSize+1)*sizeof(wchar_t))
        MultiByteToWideChar(CP_UTF8, 0, cc.c_str(), -1, pwszUnicode, iSize);
        for (int i = 0; i < iSize - 1; i++)
        {
            SendUnicode(*pwszUnicode++);
        }
        // 不要忘记恢复指针
        pwszUnicode -= (iSize - 1);
        free(pwszUnicode);
        pwszUnicode = NULL;
    }

    args.GetReturnValue().SetUndefined();
}

#pragma optimize("", on)
extern "C" NODE_MODULE_EXPORT void

NODE_MODULE_INITIALIZER(Local<Object> exports,
                        Local<Value> modules,
                        Local<Context> context)
{
    NODE_SET_METHOD(exports, "typeUnicode", typeUnicode);
}