# API 函数  

## SendInput[winuser.h]  

```c++
// windef.h
// p -> pointer;lp -> long pointer
typedef unsigned int UINT,*PUINT,*LPUINT;

// 似乎是用来加载dll 的
// #ifndef WINUSERAPI
// #ifdef __W32API_USE_DLLIMPORT__
// #define WINUSERAPI  DECLSPEC_IMPORT
// #else
// #define WINUSERAPI
// #endif
// #define DECLSPEC_IMPORT __declspec(dllimport)
//
// #define WINAPI __stdcall
WINUSERAPI UINT WINAPI SendInput (
    UINT cInputs,  // 参数pInputs 数组中结构体的个数
    LPINPUT pInputs,  // INPUT 结构体数组，每一个元素代表插入键盘/鼠标事件流的事件
    int cbSize  // 每个INPUT 结构的字节数，通常为sizeof(INPUT)。如果与实际不符函数就会失败(出错)
    );
// 运行成功返回插入的事件的个数，为0的话则表示被阻塞

// INPUT 结构
typedef struct tagINPUT {
  DWORD type;  // 0 鼠标；1 键盘；2 硬件
  union {
    MOUSEINPUT    mi;  // mouse input
    KEYBDINPUT    ki;  // keyboard input
    HARDWAREINPUT hi;  // hardware input
  } DUMMYUNIONNAME;
} INPUT, *PINPUT, *LPINPUT;


// KeyboardInput 结构
// https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/ns-winuser-keybdinput
typedef struct tagKEYBDINPUT {
  WORD      wVk;  // 虚拟键位码[0,254]，如果dwFlags 指定为KEYEVENTF_UNICODE，则此项必须为0
  WORD      wScan;  // 按键的扫描码，如果dwFlags 指定为KEYEVENTF_UNICODE，此项表示发往前台的Unicode 字符
  DWORD     dwFlags;  // 标志位：0 KEYEVENTF_EXTENDEDKEY(0x0001) KEYEVENTF_KEYUP(0x0002) KEYEVENTF_UNICODE(0x0004) KEYEVENTF_SCANCODE(0x0008)
  DWORD     time;  // 时间戳，一般默认为0，系统会设定时间戳
  ULONG_PTR dwExtraInfo;  // 额外的信息
} KEYBDINPUT, *PKEYBDINPUT, *LPKEYBDINPUT;
/**
 * INPUT_KEYBOARD 支持无键盘输入(书写、语音)，就如其通过KEYEVENTF_UNICODE 标志输入文本一样。
 * 如果KEYEVENTF_UNICODE 被指定，SendInput 会发送一个WM_KEYDOWN 或者WM_KEYUP 消息(wParam=VK_PACKET)给前台线程的消息队列。
 * 一旦GetMessage 或PeekMessage 获得消息，并传递给TranslateMessage，发出WM_CHAR 消息，此消息带有wScan 最初指定的Unicode 字符；如果将Unicode 字符发布到ASNI 窗口，它也会自动转化为ASNI 值。
 * 可以通过设置KEYEVENTF_SCANCODE 来模拟物理键盘操作输入扫描码。
 * 虚拟键位码可能会受键盘布局影响，但扫描码是不会变的
*/

// MouseInput 结构
// https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/ns-winuser-mouseinput
typedef struct tagMOUSEINPUT {
  LONG      dx;  // 绝对或相对x坐标，依赖于dwFlags 参数
  LONG      dy;  // 绝对或相对y坐标，同dx
  DWORD     mouseData;  // 鼠标事件的参数，依赖于dwFlags 参数
  DWORD     dwFlags;  // 通过位掩码表示的标志位
  DWORD     time;  // 时间戳
  ULONG_PTR dwExtraInfo;  // 额外信息
} MOUSEINPUT, *PMOUSEINPUT, *LPMOUSEINPUT;
/**
 * 绝对坐标会被归一化表示：左上(0,0)->右下(65535,65535)；
 * 如果设置了MOUSEEVENTF_VIRTUALDESK，则坐标将映射到整个虚拟桌面。
 * 相对移动受鼠标速度和阈值影响：鼠标属性可通过SystemParametersInfo 函数获取
*/

// HardwareInput 结构
// https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/ns-winuser-hardwareinput
typedef struct tagHARDWAREINPUT {
  DWORD uMsg;
  WORD  wParamL;
  WORD  wParamH;
} HARDWAREINPUT, *PHARDWAREINPUT, *LPHARDWAREINPUT;
```  

## 字符转换[winnls.h]

```c++
int MultiByteToWideChar(
  UINT CodePage,  // 目标编码字符集
  DWORD dwFlags,  // 标志
  LPCSTR lpMultiByteStr,  // 指向待转化数组
  int cbMultiByte,  // 数组长度，如果是-1的话，就会自动计算缓冲区长度
  LPWSTR lpWideCharStr,  // 生成的字符串
  int cchWideChar  // 缓冲区长度，如果是0 则返回所需的缓冲区长度
);

int WideCharToMultiByte(
  UINT CodePage,  // 源编码字符集
  DWORD dwFlags,  // 标志
  LPCWSTR lpWideCharStr,  // 源字符串
  int cchWideChar,  // 源字符串长度
  LPSTR lpMultiByteStr,  // 目标数组
  int cbMultiByte,  // 目标数组常速
  LPCSTR lpDefaultChar,  // 默认字符
  LPBOOL lpUsedDefaultChar  // 是否使用默认字符
);
```  

## 虚拟键码[winuser]

```c++
// ASCII 转虚拟键
// https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-vkkeyscanexa
SHORT VkKeyScan(
  CHAR ch
);
// 考虑键盘布局的话
SHORT VkKeyScanEx(
  CHAR ch,
  HKL  dwhkl
);
// 返回值：
//    高八位，组合键状态
//      1 -> shift
//      2 -> ctrl
//      4 -> alt
//      8 -> Hanhaku
//      ... -> 保留
//    低八位，虚拟键码

```