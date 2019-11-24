"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var nc_keyboard = require("./build/Release/nc_keyboard");
/**
 * 虚拟键盘码
 */
var vKeyCode;
(function (vKeyCode) {
    vKeyCode[vKeyCode["VK_LBUTTON"] = 1] = "VK_LBUTTON";
    vKeyCode[vKeyCode["VK_RBUTTON"] = 2] = "VK_RBUTTON";
    vKeyCode[vKeyCode["VK_CANCEL"] = 3] = "VK_CANCEL";
    vKeyCode[vKeyCode["VK_MBUTTON"] = 4] = "VK_MBUTTON";
    vKeyCode[vKeyCode["VK_XBUTTON1"] = 5] = "VK_XBUTTON1";
    vKeyCode[vKeyCode["VK_XBUTTON2"] = 6] = "VK_XBUTTON2";
    vKeyCode[vKeyCode["VK_BACK"] = 8] = "VK_BACK";
    vKeyCode[vKeyCode["VK_TAB"] = 9] = "VK_TAB";
    vKeyCode[vKeyCode["VK_CLEAR"] = 12] = "VK_CLEAR";
    vKeyCode[vKeyCode["VK_RETURN"] = 13] = "VK_RETURN";
    vKeyCode[vKeyCode["VK_SHIFT"] = 16] = "VK_SHIFT";
    vKeyCode[vKeyCode["VK_CONTROL"] = 17] = "VK_CONTROL";
    vKeyCode[vKeyCode["VK_MENU"] = 18] = "VK_MENU";
    vKeyCode[vKeyCode["VK_PAUSE"] = 19] = "VK_PAUSE";
    vKeyCode[vKeyCode["VK_CAPITAL"] = 20] = "VK_CAPITAL";
    vKeyCode[vKeyCode["VK_KANA"] = 21] = "VK_KANA";
    vKeyCode[vKeyCode["VK_HANGUL"] = 21] = "VK_HANGUL";
    vKeyCode[vKeyCode["VK_JUNJA"] = 23] = "VK_JUNJA";
    vKeyCode[vKeyCode["VK_FINAL"] = 24] = "VK_FINAL";
    vKeyCode[vKeyCode["VK_HANJA"] = 25] = "VK_HANJA";
    vKeyCode[vKeyCode["VK_KANJI"] = 25] = "VK_KANJI";
    vKeyCode[vKeyCode["VK_ESCAPE"] = 27] = "VK_ESCAPE";
    vKeyCode[vKeyCode["VK_CONVERT"] = 28] = "VK_CONVERT";
    vKeyCode[vKeyCode["VK_NONCONVERT"] = 29] = "VK_NONCONVERT";
    vKeyCode[vKeyCode["VK_ACCEPT"] = 30] = "VK_ACCEPT";
    vKeyCode[vKeyCode["VK_MODECHANGE"] = 31] = "VK_MODECHANGE";
    vKeyCode[vKeyCode["VK_SPACE"] = 32] = "VK_SPACE";
    vKeyCode[vKeyCode["VK_PRIOR"] = 33] = "VK_PRIOR";
    vKeyCode[vKeyCode["VK_NEXT"] = 34] = "VK_NEXT";
    vKeyCode[vKeyCode["VK_END"] = 35] = "VK_END";
    vKeyCode[vKeyCode["VK_HOME"] = 36] = "VK_HOME";
    vKeyCode[vKeyCode["VK_LEFT"] = 37] = "VK_LEFT";
    vKeyCode[vKeyCode["VK_UP"] = 38] = "VK_UP";
    vKeyCode[vKeyCode["VK_RIGHT"] = 39] = "VK_RIGHT";
    vKeyCode[vKeyCode["VK_DOWN"] = 40] = "VK_DOWN";
    vKeyCode[vKeyCode["VK_SELECT"] = 41] = "VK_SELECT";
    vKeyCode[vKeyCode["VK_PRINT"] = 42] = "VK_PRINT";
    vKeyCode[vKeyCode["VK_EXECUTE"] = 43] = "VK_EXECUTE";
    vKeyCode[vKeyCode["VK_SNAPSHOT"] = 44] = "VK_SNAPSHOT";
    vKeyCode[vKeyCode["VK_INSERT"] = 45] = "VK_INSERT";
    vKeyCode[vKeyCode["VK_DELETE"] = 46] = "VK_DELETE";
    vKeyCode[vKeyCode["VK_HELP"] = 47] = "VK_HELP";
    vKeyCode[vKeyCode["VK_0"] = 48] = "VK_0";
    vKeyCode[vKeyCode["VK_1"] = 49] = "VK_1";
    vKeyCode[vKeyCode["VK_2"] = 50] = "VK_2";
    vKeyCode[vKeyCode["VK_3"] = 51] = "VK_3";
    vKeyCode[vKeyCode["VK_4"] = 52] = "VK_4";
    vKeyCode[vKeyCode["VK_5"] = 53] = "VK_5";
    vKeyCode[vKeyCode["VK_6"] = 54] = "VK_6";
    vKeyCode[vKeyCode["VK_7"] = 55] = "VK_7";
    vKeyCode[vKeyCode["VK_8"] = 56] = "VK_8";
    vKeyCode[vKeyCode["VK_9"] = 57] = "VK_9";
    vKeyCode[vKeyCode["VK_A"] = 65] = "VK_A";
    vKeyCode[vKeyCode["VK_B"] = 66] = "VK_B";
    vKeyCode[vKeyCode["VK_C"] = 67] = "VK_C";
    vKeyCode[vKeyCode["VK_D"] = 68] = "VK_D";
    vKeyCode[vKeyCode["VK_E"] = 69] = "VK_E";
    vKeyCode[vKeyCode["VK_F"] = 70] = "VK_F";
    vKeyCode[vKeyCode["VK_G"] = 71] = "VK_G";
    vKeyCode[vKeyCode["VK_H"] = 72] = "VK_H";
    vKeyCode[vKeyCode["VK_I"] = 73] = "VK_I";
    vKeyCode[vKeyCode["VK_J"] = 74] = "VK_J";
    vKeyCode[vKeyCode["VK_K"] = 75] = "VK_K";
    vKeyCode[vKeyCode["VK_L"] = 76] = "VK_L";
    vKeyCode[vKeyCode["VK_M"] = 77] = "VK_M";
    vKeyCode[vKeyCode["VK_N"] = 78] = "VK_N";
    vKeyCode[vKeyCode["VK_O"] = 79] = "VK_O";
    vKeyCode[vKeyCode["VK_P"] = 80] = "VK_P";
    vKeyCode[vKeyCode["VK_Q"] = 81] = "VK_Q";
    vKeyCode[vKeyCode["VK_R"] = 82] = "VK_R";
    vKeyCode[vKeyCode["VK_S"] = 83] = "VK_S";
    vKeyCode[vKeyCode["VK_T"] = 84] = "VK_T";
    vKeyCode[vKeyCode["VK_U"] = 85] = "VK_U";
    vKeyCode[vKeyCode["VK_V"] = 86] = "VK_V";
    vKeyCode[vKeyCode["VK_W"] = 87] = "VK_W";
    vKeyCode[vKeyCode["VK_X"] = 88] = "VK_X";
    vKeyCode[vKeyCode["VK_Y"] = 89] = "VK_Y";
    vKeyCode[vKeyCode["VK_Z"] = 90] = "VK_Z";
    vKeyCode[vKeyCode["VK_LWIN"] = 91] = "VK_LWIN";
    vKeyCode[vKeyCode["VK_RWIN"] = 92] = "VK_RWIN";
    vKeyCode[vKeyCode["VK_APPS"] = 93] = "VK_APPS";
    vKeyCode[vKeyCode["VK_SLEEP"] = 95] = "VK_SLEEP";
    vKeyCode[vKeyCode["VK_NUMPAD0"] = 96] = "VK_NUMPAD0";
    vKeyCode[vKeyCode["VK_NUMPAD1"] = 97] = "VK_NUMPAD1";
    vKeyCode[vKeyCode["VK_NUMPAD2"] = 98] = "VK_NUMPAD2";
    vKeyCode[vKeyCode["VK_NUMPAD3"] = 99] = "VK_NUMPAD3";
    vKeyCode[vKeyCode["VK_NUMPAD4"] = 100] = "VK_NUMPAD4";
    vKeyCode[vKeyCode["VK_NUMPAD5"] = 101] = "VK_NUMPAD5";
    vKeyCode[vKeyCode["VK_NUMPAD6"] = 102] = "VK_NUMPAD6";
    vKeyCode[vKeyCode["VK_NUMPAD7"] = 103] = "VK_NUMPAD7";
    vKeyCode[vKeyCode["VK_NUMPAD8"] = 104] = "VK_NUMPAD8";
    vKeyCode[vKeyCode["VK_NUMPAD9"] = 105] = "VK_NUMPAD9";
    vKeyCode[vKeyCode["VK_MULTIPLY"] = 106] = "VK_MULTIPLY";
    vKeyCode[vKeyCode["VK_ADD"] = 107] = "VK_ADD";
    vKeyCode[vKeyCode["VK_SEPARATOR"] = 108] = "VK_SEPARATOR";
    vKeyCode[vKeyCode["VK_SUBTRACT"] = 109] = "VK_SUBTRACT";
    vKeyCode[vKeyCode["VK_DECIMAL"] = 110] = "VK_DECIMAL";
    vKeyCode[vKeyCode["VK_DIVIDE"] = 111] = "VK_DIVIDE";
    vKeyCode[vKeyCode["VK_F1"] = 112] = "VK_F1";
    vKeyCode[vKeyCode["VK_F2"] = 113] = "VK_F2";
    vKeyCode[vKeyCode["VK_F3"] = 114] = "VK_F3";
    vKeyCode[vKeyCode["VK_F4"] = 115] = "VK_F4";
    vKeyCode[vKeyCode["VK_F5"] = 116] = "VK_F5";
    vKeyCode[vKeyCode["VK_F6"] = 117] = "VK_F6";
    vKeyCode[vKeyCode["VK_F7"] = 118] = "VK_F7";
    vKeyCode[vKeyCode["VK_F8"] = 119] = "VK_F8";
    vKeyCode[vKeyCode["VK_F9"] = 120] = "VK_F9";
    vKeyCode[vKeyCode["VK_F10"] = 121] = "VK_F10";
    vKeyCode[vKeyCode["VK_F11"] = 122] = "VK_F11";
    vKeyCode[vKeyCode["VK_F12"] = 123] = "VK_F12";
    vKeyCode[vKeyCode["VK_F13"] = 124] = "VK_F13";
    vKeyCode[vKeyCode["VK_F14"] = 125] = "VK_F14";
    vKeyCode[vKeyCode["VK_F15"] = 126] = "VK_F15";
    vKeyCode[vKeyCode["VK_F16"] = 127] = "VK_F16";
    vKeyCode[vKeyCode["VK_F17"] = 128] = "VK_F17";
    vKeyCode[vKeyCode["VK_F18"] = 129] = "VK_F18";
    vKeyCode[vKeyCode["VK_F19"] = 130] = "VK_F19";
    vKeyCode[vKeyCode["VK_F20"] = 131] = "VK_F20";
    vKeyCode[vKeyCode["VK_F21"] = 132] = "VK_F21";
    vKeyCode[vKeyCode["VK_F22"] = 133] = "VK_F22";
    vKeyCode[vKeyCode["VK_F23"] = 134] = "VK_F23";
    vKeyCode[vKeyCode["VK_F24"] = 135] = "VK_F24";
    vKeyCode[vKeyCode["VK_NUMLOCK"] = 144] = "VK_NUMLOCK";
    vKeyCode[vKeyCode["VK_SCROLL"] = 145] = "VK_SCROLL";
    vKeyCode[vKeyCode["VK_LSHIFT"] = 160] = "VK_LSHIFT";
    vKeyCode[vKeyCode["VK_RSHIFT"] = 161] = "VK_RSHIFT";
    vKeyCode[vKeyCode["VK_LCONTROL"] = 162] = "VK_LCONTROL";
    vKeyCode[vKeyCode["VK_RCONTROL"] = 163] = "VK_RCONTROL";
    vKeyCode[vKeyCode["VK_LMENU"] = 164] = "VK_LMENU";
    vKeyCode[vKeyCode["VK_RMENU"] = 165] = "VK_RMENU";
    vKeyCode[vKeyCode["VK_BROWSER_BACK"] = 166] = "VK_BROWSER_BACK";
    vKeyCode[vKeyCode["VK_BROWSER_FORWARD"] = 167] = "VK_BROWSER_FORWARD";
    vKeyCode[vKeyCode["VK_BROWSER_REFRESH"] = 168] = "VK_BROWSER_REFRESH";
    vKeyCode[vKeyCode["VK_BROWSER_STOP"] = 169] = "VK_BROWSER_STOP";
    vKeyCode[vKeyCode["VK_BROWSER_SEARCH"] = 170] = "VK_BROWSER_SEARCH";
    vKeyCode[vKeyCode["VK_BROWSER_FAVORITES"] = 171] = "VK_BROWSER_FAVORITES";
    vKeyCode[vKeyCode["VK_BROWSER_HOME"] = 172] = "VK_BROWSER_HOME";
    vKeyCode[vKeyCode["VK_VOLUME_MUTE"] = 173] = "VK_VOLUME_MUTE";
    vKeyCode[vKeyCode["VK_VOLUME_DOWN"] = 174] = "VK_VOLUME_DOWN";
    vKeyCode[vKeyCode["VK_VOLUME_UP"] = 175] = "VK_VOLUME_UP";
    vKeyCode[vKeyCode["VK_MEDIA_NEXT_TRACK"] = 176] = "VK_MEDIA_NEXT_TRACK";
    vKeyCode[vKeyCode["VK_MEDIA_PREV_TRACK"] = 177] = "VK_MEDIA_PREV_TRACK";
    vKeyCode[vKeyCode["VK_MEDIA_STOP"] = 178] = "VK_MEDIA_STOP";
    vKeyCode[vKeyCode["VK_MEDIA_PLAY_PAUSE"] = 179] = "VK_MEDIA_PLAY_PAUSE";
    vKeyCode[vKeyCode["VK_LAUNCH_MAIL"] = 180] = "VK_LAUNCH_MAIL";
    vKeyCode[vKeyCode["VK_LAUNCH_MEDIA_SELECT"] = 181] = "VK_LAUNCH_MEDIA_SELECT";
    vKeyCode[vKeyCode["VK_LAUNCH_APP1"] = 182] = "VK_LAUNCH_APP1";
    vKeyCode[vKeyCode["VK_LAUNCH_APP2"] = 183] = "VK_LAUNCH_APP2";
    vKeyCode[vKeyCode["VK_OEM_1"] = 186] = "VK_OEM_1";
    vKeyCode[vKeyCode["VK_OEM_PLUS"] = 187] = "VK_OEM_PLUS";
    vKeyCode[vKeyCode["VK_OEM_COMMA"] = 188] = "VK_OEM_COMMA";
    vKeyCode[vKeyCode["VK_OEM_MINUS"] = 189] = "VK_OEM_MINUS";
    vKeyCode[vKeyCode["VK_OEM_PERIOD"] = 190] = "VK_OEM_PERIOD";
    vKeyCode[vKeyCode["VK_OEM_2"] = 191] = "VK_OEM_2";
    vKeyCode[vKeyCode["VK_OEM_3"] = 192] = "VK_OEM_3";
    vKeyCode[vKeyCode["VK_OEM_4"] = 219] = "VK_OEM_4";
    vKeyCode[vKeyCode["VK_OEM_5"] = 220] = "VK_OEM_5";
    vKeyCode[vKeyCode["VK_OEM_6"] = 221] = "VK_OEM_6";
    vKeyCode[vKeyCode["VK_OEM_7"] = 222] = "VK_OEM_7";
    vKeyCode[vKeyCode["VK_OEM_8"] = 223] = "VK_OEM_8";
    vKeyCode[vKeyCode["VK_OEM_102"] = 226] = "VK_OEM_102";
    vKeyCode[vKeyCode["VK_PACKET"] = 231] = "VK_PACKET";
    vKeyCode[vKeyCode["VK_PROCESSKEY"] = 229] = "VK_PROCESSKEY";
    vKeyCode[vKeyCode["VK_ATTN"] = 246] = "VK_ATTN";
    vKeyCode[vKeyCode["VK_CRSEL"] = 247] = "VK_CRSEL";
    vKeyCode[vKeyCode["VK_EXSEL"] = 248] = "VK_EXSEL";
    vKeyCode[vKeyCode["VK_EREOF"] = 249] = "VK_EREOF";
    vKeyCode[vKeyCode["VK_PLAY"] = 250] = "VK_PLAY";
    vKeyCode[vKeyCode["VK_ZOOM"] = 251] = "VK_ZOOM";
    vKeyCode[vKeyCode["VK_NONAME"] = 252] = "VK_NONAME";
    vKeyCode[vKeyCode["VK_PA1"] = 253] = "VK_PA1";
    vKeyCode[vKeyCode["VK_OEM_CLEAR"] = 254] = "VK_OEM_CLEAR";
})(vKeyCode = exports.vKeyCode || (exports.vKeyCode = {}));
;
/**
 * 按键按下
 * @param code 虚拟键盘码
 */
function keyDown(code) {
    nc_keyboard.keyDown(code);
}
exports.keyDown = keyDown;
/**
 * 按键弹起
 * @param code 虚拟键盘码
 */
function keyUp(code) {
    nc_keyboard.keyUp(code);
}
exports.keyUp = keyUp;
/**
 * 输入虚拟键盘码
 * @param codes 虚拟键盘码 可变参数
 */
function typeVKeys() {
    var codes = [];
    for (var _i = 0; _i < arguments.length; _i++) {
        codes[_i] = arguments[_i];
    }
    nc_keyboard.typeVKeys.apply(typeVKeys, arguments);
}
exports.typeVKeys = typeVKeys;
/**
 * 输入ASCII码
 * @param codes ASCII码字符串 可变参数
 * @summary 与大小写无关，但是跟键盘有关，建议用typeUnicode
 */
function typeAscii() {
    var codes = [];
    for (var _i = 0; _i < arguments.length; _i++) {
        codes[_i] = arguments[_i];
    }
    nc_keyboard.typeAscii.apply(typeAscii, arguments);
}
exports.typeAscii = typeAscii;
/**
 * 输入Unicode码
 * @param codes Unicode码字符串 可变参数
 */
function typeUnicode() {
    var codes = [];
    for (var _i = 0; _i < arguments.length; _i++) {
        codes[_i] = arguments[_i];
    }
    nc_keyboard.typeUnicode.apply(typeUnicode, arguments);
}
exports.typeUnicode = typeUnicode;
/**
 * 输入Unicode码
 * @param codes Unicode码字符串 可变参数
 * @summary 鉴于纯输出ASCII 并不能完全避免输入法引起的大小写问题
 * 所以，将ASCII 码中的字符与符号作为Unicode 输入
 */
function typeUniAscii() {
    var codes = [];
    for (var _i = 0; _i < arguments.length; _i++) {
        codes[_i] = arguments[_i];
    }
    nc_keyboard.typeUnicode.apply(typeUniAscii, arguments);
}
exports.typeUniAscii = typeUniAscii;
