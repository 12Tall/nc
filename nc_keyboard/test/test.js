const nc_keyboard = require("../build/Release/nc_keyboard")

nc_keyboard.typeVirtualKey(65, 66, 67, 68, 69.5);

nc_keyboard.keyDown(16);
nc_keyboard.keyDown(65);
nc_keyboard.keyDown(65);
nc_keyboard.keyUp(16);
nc_keyboard.keyUp(65);
nc_keyboard.keyUp(65);