const nc_keyboard = require("../build/Release/nc_keyboard")

// 虚拟键盘码
nc_keyboard.typeVirtualKey(65, 66, 67, 68, 69.5);
// ASCII 码
nc_keyboard.typeAscii("hello world!");
// Unicode
nc_keyboard.typeUnicode("你好，世界！");

// 按键 A
nc_keyboard.keyDown(16);
nc_keyboard.keyDown(65);
nc_keyboard.keyUp(65);
nc_keyboard.keyUp(16);