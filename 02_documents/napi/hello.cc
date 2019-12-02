#include <node_api.h>

namespace demo
{
napi_value Method(napi_env env, napi_callback_info args)
{
    napi_value greeting;
    napi_status status;

    status = napi_create_string_utf8(env,     // 环境
                                     "world", // 值
                                     NAPI_AUTO_LENGTH,
                                     &greeting);
    if (status != napi_ok)
    {
        return nullptr;
    }
    return greeting;
}

napi_value init(napi_env env, napi_value exports)
{
    napi_status status;
    napi_value fn;

    // 从函数创建函数
    status = napi_create_function(env, nullptr, 0, Method, nullptr, &fn);
    if (status != napi_ok)
    {
        return nullptr;
    }
    // 将函数绑定到属性
    status = napi_set_named_property(env, exports, "hello", fn);
    if (status != napi_ok)
    {
        return nullptr;
    }

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

} // namespace demo