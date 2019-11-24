declare function require(name: string): any;
const nc_keyboard = require("./build/Release/nc_keyboard");
/**
 * 虚拟键盘码
 */
export enum vKeyCode {
    VK_LBUTTON = 1,  // 鼠标左键
    VK_RBUTTON = 2,  // 鼠标右键
    VK_CANCEL = 3,  // Cancel
    VK_MBUTTON = 4,  // 鼠标中键
    VK_XBUTTON1 = 5,  // 
    VK_XBUTTON2 = 6,  // 
    VK_BACK = 8,  // Backspace
    VK_TAB = 9,  // Tab
    VK_CLEAR = 12,  // Clear
    VK_RETURN = 13,  // Enter
    VK_SHIFT = 16,  // Shift
    VK_CONTROL = 17,  // Ctrl
    VK_MENU = 18,  // Alt
    VK_PAUSE = 19,  // Pause
    VK_CAPITAL = 20,  // Caps Lock
    VK_KANA = 21,  // 
    VK_HANGUL = 21,  // 
    VK_JUNJA = 23,  // 
    VK_FINAL = 24,  // 
    VK_HANJA = 25,  // 
    VK_KANJI = 25,  // VK_KANJI = 25*, 
    VK_ESCAPE = 27,  // Esc
    VK_CONVERT = 28,  // 
    VK_NONCONVERT = 29,  // 
    VK_ACCEPT = 30,  // 
    VK_MODECHANGE = 31,  // 
    VK_SPACE = 32,  // Space
    VK_PRIOR = 33,  // Page Up
    VK_NEXT = 34,  // Page Down
    VK_END = 35,  // End
    VK_HOME = 36,  // Home
    VK_LEFT = 37,  // Left Arrow
    VK_UP = 38,  // Up Arrow
    VK_RIGHT = 39,  // Right Arrow
    VK_DOWN = 40,  // Down Arrow
    VK_SELECT = 41,  // Select
    VK_PRINT = 42,  // Print
    VK_EXECUTE = 43,  // Execute
    VK_SNAPSHOT = 44,  // Snapshot
    VK_INSERT = 45,  // Insert
    VK_DELETE = 46,  // Delete
    VK_HELP = 47,  // Help
    VK_0 = 48,  // 0
    VK_1 = 49,  // 1
    VK_2 = 50,  // 2
    VK_3 = 51,  // 3
    VK_4 = 52,  // 4
    VK_5 = 53,  // 5
    VK_6 = 54,  // 6
    VK_7 = 55,  // 7
    VK_8 = 56,  // 8
    VK_9 = 57,  // 9
    VK_A = 65,  // A
    VK_B = 66,  // B
    VK_C = 67,  // C
    VK_D = 68,  // D
    VK_E = 69,  // E
    VK_F = 70,  // F
    VK_G = 71,  // G
    VK_H = 72,  // H
    VK_I = 73,  // I
    VK_J = 74,  // J
    VK_K = 75,  // K
    VK_L = 76,  // L
    VK_M = 77,  // M
    VK_N = 78,  // N
    VK_O = 79,  // O
    VK_P = 80,  // P
    VK_Q = 81,  // Q
    VK_R = 82,  // R
    VK_S = 83,  // S
    VK_T = 84,  // T
    VK_U = 85,  // U
    VK_V = 86,  // V
    VK_W = 87,  // W
    VK_X = 88,  // X
    VK_Y = 89,  // Y
    VK_Z = 90,  // Z
    VK_LWIN = 91,  // 
    VK_RWIN = 92,  // 
    VK_APPS = 93,  // 
    VK_SLEEP = 95,  // 
    VK_NUMPAD0 = 96,  // 小键盘 0
    VK_NUMPAD1 = 97,  // 小键盘 1
    VK_NUMPAD2 = 98,  // 小键盘 2
    VK_NUMPAD3 = 99,  // 小键盘 3
    VK_NUMPAD4 = 100,  // 小键盘 4
    VK_NUMPAD5 = 101,  // 小键盘 5
    VK_NUMPAD6 = 102,  // 小键盘 6
    VK_NUMPAD7 = 103,  // 小键盘 7
    VK_NUMPAD8 = 104,  // 小键盘 8
    VK_NUMPAD9 = 105,  // 小键盘 9
    VK_MULTIPLY = 106,  // 小键盘 *
    VK_ADD = 107,  // 小键盘 +
    VK_SEPARATOR = 108,  // 小键盘 Enter
    VK_SUBTRACT = 109,  // 小键盘 -
    VK_DECIMAL = 110,  // 小键盘 .
    VK_DIVIDE = 111,  // 小键盘 /
    VK_F1 = 112,  // F1
    VK_F2 = 113,  // F2
    VK_F3 = 114,  // F3
    VK_F4 = 115,  // F4
    VK_F5 = 116,  // F5
    VK_F6 = 117,  // F6
    VK_F7 = 118,  // F7
    VK_F8 = 119,  // F8
    VK_F9 = 120,  // F9
    VK_F10 = 121,  // F10
    VK_F11 = 122,  // F11
    VK_F12 = 123,  // F12
    VK_F13 = 124,  // 
    VK_F14 = 125,  // 
    VK_F15 = 126,  // 
    VK_F16 = 127,  // 
    VK_F17 = 128,  // 
    VK_F18 = 129,  // 
    VK_F19 = 130,  // 
    VK_F20 = 131,  // 
    VK_F21 = 132,  // 
    VK_F22 = 133,  // 
    VK_F23 = 134,  // 
    VK_F24 = 135,  // 
    VK_NUMLOCK = 144,  // Num Lock
    VK_SCROLL = 145,  // Scroll
    VK_LSHIFT = 160,  // 
    VK_RSHIFT = 161,  // 
    VK_LCONTROL = 162,  // 
    VK_RCONTROL = 163,  // 
    VK_LMENU = 164,  // 
    VK_RMENU = 165,  // 
    VK_BROWSER_BACK = 166,  // 
    VK_BROWSER_FORWARD = 167,  // 
    VK_BROWSER_REFRESH = 168,  // 
    VK_BROWSER_STOP = 169,  // 
    VK_BROWSER_SEARCH = 170,  // 
    VK_BROWSER_FAVORITES = 171,  // 
    VK_BROWSER_HOME = 172,  // 
    VK_VOLUME_MUTE = 173,  // VolumeMute
    VK_VOLUME_DOWN = 174,  // VolumeDown
    VK_VOLUME_UP = 175,  // VolumeUp
    VK_MEDIA_NEXT_TRACK = 176,  // 
    VK_MEDIA_PREV_TRACK = 177,  // 
    VK_MEDIA_STOP = 178,  // 
    VK_MEDIA_PLAY_PAUSE = 179,  // 
    VK_LAUNCH_MAIL = 180,  // 
    VK_LAUNCH_MEDIA_SELECT = 181,  // 
    VK_LAUNCH_APP1 = 182,  // 
    VK_LAUNCH_APP2 = 183,  // 
    VK_OEM_1 = 186,  // ; :
    VK_OEM_PLUS = 187,  // = +
    VK_OEM_COMMA = 188,  // 
    VK_OEM_MINUS = 189,  // - _
    VK_OEM_PERIOD = 190,  // 
    VK_OEM_2 = 191,  // / ?
    VK_OEM_3 = 192,  // ` ~
    VK_OEM_4 = 219,  // [ {
    VK_OEM_5 = 220,  // \ |
    VK_OEM_6 = 221,  // ] }
    VK_OEM_7 = 222,  // ' "
    VK_OEM_8 = 223,  // 
    VK_OEM_102 = 226,  // 
    VK_PACKET = 231,  // 
    VK_PROCESSKEY = 229,  // 
    VK_ATTN = 246,  // 
    VK_CRSEL = 247,  // 
    VK_EXSEL = 248,  // 
    VK_EREOF = 249,  // 
    VK_PLAY = 250,  // 
    VK_ZOOM = 251,  // 
    VK_NONAME = 252,  // 
    VK_PA1 = 253,  // 
    VK_OEM_CLEAR = 254,  // 

};
/**
 * 按键按下
 * @param code 虚拟键盘码
 */
export function keyDown(code: vKeyCode): void {
    nc_keyboard.keyDown(code);
}

/**
 * 按键弹起
 * @param code 虚拟键盘码
 */
export function keyUp(code: vKeyCode): void {
    nc_keyboard.keyUp(code);
}

/**
 * 输入虚拟键盘码
 * @param codes 虚拟键盘码 可变参数
 */
export function typeVKeys(...codes: Array<vKeyCode>): void {
    nc_keyboard.typeVKeys.apply(typeVKeys, arguments);
}

/**
 * 输入ASCII码
 * @param codes ASCII码字符串 可变参数
 * @summary 与大小写无关，但是跟键盘有关，建议用typeUnicode
 */
export function typeAscii(...codes: Array<string>): void {
    nc_keyboard.typeAscii.apply(typeAscii, arguments);
}

/**
 * 输入Unicode码
 * @param codes Unicode码字符串 可变参数
 */
export function typeUnicode(...codes: Array<string>): void {
    nc_keyboard.typeUnicode.apply(typeUnicode, arguments);
}

/**
 * 输入Unicode码
 * @param codes Unicode码字符串 可变参数
 * @summary 鉴于纯输出ASCII 并不能完全避免输入法引起的大小写问题
 * 所以，将ASCII 码中的字符与符号作为Unicode 输入
 */
export function typeUniAscii(...codes: Array<string>): void {
    nc_keyboard.typeUnicode.apply(typeUniAscii, arguments);
}
