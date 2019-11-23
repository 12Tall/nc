#pragma once
#ifndef __KEYBOARD_WIN_H__
#define __KEYBOARD_WIN_H__

#include <node.h>
#include <v8.h>
#include <windows.h>
#include <winuser.h>

using namespace v8;
using namespace std;

void KeyDown(WORD vKey);
void KeyUp(WORD vKey);
void SendKey(WORD vKey);
void SendAscii(char vkKey);
void SendUnicode(wchar_t data);

#endif
/**
 * keyboard_win.h
 * 键盘宏
 * */

/**
 * error C2129: 静态函数“void SendKey(WORD)”已声明但未定义
 * 静态函数只能在声明它的文件当中可见，不能被其他文件所调用，
 * 也就是说该静态函数只能在其定义的.cpp或.c中调用，
 * 在其它.cpp或.c文件的函数里是不能被调用的。
*/