const nc = require("../build/Release/nc");
var i = 0;
nc.typeUnicode(`\\\n${i++}秒`);
nc.typeUnicode(`${i++}秒\n\r`);
nc.typeUnicode(`${i++}秒\n\r`);
nc.typeUnicode(`${i++}秒`);
nc.typeUnicode(`${i++}秒`);
nc.typeUnicode(`${i++}秒`);