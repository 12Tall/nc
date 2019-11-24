#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include "keyboard_win.h"

using namespace v8;
using namespace std;

void KeyDown(WORD vKey)
{
    INPUT input;
    memset(&input, 0, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vKey;

    SendInput(1, &input, sizeof(INPUT));
}
void KeyUp(WORD vKey)
{
    INPUT input;
    memset(&input, 0, sizeof(INPUT));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vKey;
    input.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}

void SendKey(WORD vKey)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = vKey;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = vKey;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}

void SendAscii(wchar_t ch)
{
    short ch2 = VkKeyScanW(ch);
    ShiftState *state = (ShiftState *)&ch2;
    // 大写已按下
    if (GetKeyState(VK_CAPITAL) & 0x1)
    {
        // 且属于字母
        if (state->ch >= 'a' && state->ch <= 'z' || state->ch >= 'A' && state->ch <= 'Z')
        {
            state->shift = !state->shift;
        }
    }
    if (state->shift == 1)
    {
        KeyDown(VK_SHIFT);
    }
    SendKey(state->ch);

    if (state->shift == 1)
    {
        KeyUp(VK_SHIFT);
    }
}

void SendUniAscii(wchar_t ch)
{
    short ch2 = VkKeyScanW(ch);
    ShiftState *state = (ShiftState *)&ch2;

    // 且属于字母
    if ((state->ch >= '!' && state->ch <= '~') || ch > 255)
    {
        INPUT input[2];
        memset(input, 0, 2 * sizeof(INPUT));
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wScan = ch;
        input[0].ki.dwFlags = KEYEVENTF_UNICODE;

        input[1].type = INPUT_KEYBOARD;
        input[1].ki.wScan = ch;
        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;

        SendInput(2, input, sizeof(INPUT));
    }
    else
    {
        if (state->shift == 1)
        {
            KeyDown(VK_SHIFT);
        }
        SendKey(state->ch);
        if (state->shift == 1)
        {
            KeyUp(VK_SHIFT);
        }
    }
}
void SendUnicode(wchar_t ch)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wScan = ch;
    input[0].ki.dwFlags = KEYEVENTF_UNICODE;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wScan = ch;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;

    SendInput(2, input, sizeof(INPUT));
}