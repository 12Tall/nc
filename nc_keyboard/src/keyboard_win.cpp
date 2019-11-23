#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include "keyboard_win.h"

using namespace v8;
using namespace std;

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