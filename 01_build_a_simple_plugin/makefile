test:build test.js
	node test.js
# 生成文件
build:configure  
	node-gyp build
# 通过binding.gyp 生成项目构建文件
configure:binding.gyp hello.cc
	node-gyp configure