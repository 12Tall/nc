# nc  

学习下nodejs 与C++吧  
名称有点过分了  
哈哈哈哈

## [1. 构建](http://nodejs.cn/api/addons.html#addons_building)  

- 安装[node-gyp](https://github.com/nodejs/node-gyp#installation)  
- 编写[`binding.gyp`](https://github.com/nodejs/node-gyp#the-bindinggyp-file)构建配置文件  
- `node-gyp configure`生成项目文件  
- `node-gyp build`构建  

**⚠：** 文档中的例子可能太老了，构建会出现异常  

```log
error C4430: 缺少类型说明符 - 假定为 int。注意: C++ 不支持默认 int
```

## [2. 知识点](https://nodeaddons.com/)  

### [2.1 Node.js 和C++ 间的类型转换](https://fed.taobao.org/blog/2016/09/21/type-casts-between-node-and-cpp/)  
