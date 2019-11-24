const nc_keyboard = require("nc_keyboard")

// 关于虚拟键盘码并未封装完全，具体需要百度或谷歌
// 按键
nc_keyboard.keyDown(16);
nc_keyboard.keyDown(65);
nc_keyboard.keyUp(65);
nc_keyboard.keyUp(16);
// 虚拟键盘码
nc_keyboard.typeVirtualKey(65, 66, 67, 68, 69.5);


// ASCII 码
nc_keyboard.typeAscii("hello world!");
// Unicode
nc_keyboard.typeUnicode("你好，世界！");
// 新增混合输入Unicode和ASCII 的方法，
// 以避免因输入法引起的大小写一场
nc_keyboard.typeUniAscii("!!!我&￥$!!");