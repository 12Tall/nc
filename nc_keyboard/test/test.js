const nc_keyboard = require("../build/Release/nc_keyboard")

// nc_keyboard.typeVirtualKey(65, 66, 67, 68, 69.5);
// nc_keyboard.typeAscii("\a\\");
setInterval(function(){
    nc_keyboard.typeUnicode("\n我是\n123\nsdf");
},3000);
// console.log("\a")

// nc_keyboard.keyDown(16);
// nc_keyboard.keyDown(65);
// nc_keyboard.keyDown(65);
// nc_keyboard.keyUp(16);
// nc_keyboard.keyUp(65);
// nc_keyboard.keyUp(65);