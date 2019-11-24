#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include "keyboard_win.h"

using namespace v8;
using namespace std;

// 模拟连续按键
#pragma optimize("", off)
static void typeAscii(const FunctionCallbackInfo<Value> &args)
{
    int len = args.Length();
    Isolate *isolate = args.GetIsolate();
    for (int i = 0; i < len; i++)
    {
        if (args[i]->IsString())
        {
            Local<String> raw = Local<String>::Cast(args[i]);
            String::Utf8Value value(raw);
            string str = string(*value);

            int iSize;
            wchar_t *strUnicode;

            iSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
            strUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));           //不需要 pwszUnicode = (wchar_t *)malloc((iSize+1)*sizeof(wchar_t))
            MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, strUnicode, iSize);
            for (int i = 0; i < iSize - 1; i++)
            {
                SendAscii(*strUnicode++);
            }
            // 不要忘记恢复指针
            strUnicode -= (iSize - 1);
            free(strUnicode);
            strUnicode = NULL;
        }
    }
    args.GetReturnValue().SetUndefined();
}
static void typeUnicode(const FunctionCallbackInfo<Value> &args)
{
    int len = args.Length();
    Isolate *isolate = args.GetIsolate();
    for (int i = 0; i < len; i++)
    {
        if (args[i]->IsString())
        {
            Local<String> raw = Local<String>::Cast(args[i]);
            String::Utf8Value value(raw);
            string str = string(*value);

            int iSize;
            wchar_t *strUnicode;

            iSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
            strUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));           //不需要 pwszUnicode = (wchar_t *)malloc((iSize+1)*sizeof(wchar_t))
            MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, strUnicode, iSize);
            for (int i = 0; i < iSize - 1; i++)
            {
                SendUnicode(*strUnicode++);
            }
            // 不要忘记恢复指针
            strUnicode -= (iSize - 1);
            free(strUnicode);
            strUnicode = NULL;
        }
    }
    args.GetReturnValue().SetUndefined();
}

static void typeUniAscii(const FunctionCallbackInfo<Value> &args)
{
    int len = args.Length();
    Isolate *isolate = args.GetIsolate();
    for (int i = 0; i < len; i++)
    {
        if (args[i]->IsString())
        {
            Local<String> raw = Local<String>::Cast(args[i]);
            String::Utf8Value value(raw);
            string str = string(*value);

            int iSize;
            wchar_t *strUnicode;

            iSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
            strUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t));           //不需要 pwszUnicode = (wchar_t *)malloc((iSize+1)*sizeof(wchar_t))
            MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, strUnicode, iSize);
            for (int i = 0; i < iSize - 1; i++)
            {
                SendUniAscii(*strUnicode++);
            }
            // 不要忘记恢复指针
            strUnicode -= (iSize - 1);
            free(strUnicode);
            strUnicode = NULL;
        }
    }
    args.GetReturnValue().SetUndefined();
}
// 模拟连续按键
static void typeVKeys(const FunctionCallbackInfo<Value> &args)
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
    NODE_SET_METHOD(exports, "typeVKeys", typeVKeys);
    NODE_SET_METHOD(exports, "typeAscii", typeAscii);
    NODE_SET_METHOD(exports, "typeUnicode", typeUnicode);
    NODE_SET_METHOD(exports, "typeUniAscii", typeUniAscii);
    NODE_SET_METHOD(exports, "keyDown", keyDown);
    NODE_SET_METHOD(exports, "keyUp", keyUp);
}
#pragma optimize("", on)