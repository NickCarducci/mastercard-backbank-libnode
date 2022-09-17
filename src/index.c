//https://github.com/mmomtchev/libnode/blob/main/examples/axios-example-es6.cc
#include <stdio.h>
#define NAPI_EXPERIMENTAL
#define NAPI_EMBEDDING
#include <napi.h>

int main() {
    try {
        Napi::Platform platform;
        Napi::PlatformEnv env(platform);

        try {
            Napi::HandleScope scope(env);

            Napi::Function import =
                env.Global().Get("import").As<Napi::Function>();

            Napi::Value axios_promise = import.MakeCallback(
                env.Global(), {Napi::String::New(env, "axios")});

            Napi::Object axios_import =
                axios_promise.As<Napi::Promise>().Await().ToObject();
            Napi::Object axios = axios_import.Get("default").ToObject();

            Napi::Promise r =
                axios.Get("get")
                    .As<Napi::Function>()
                    .Call({Napi::String::New(env, "https://www.google.com")})
                    .As<Napi::Promise>();
            r.Get("then").As<Napi::Function>().Call(
                r,
                {Napi::Function::New(env, [](const Napi::CallbackInfo &info) {
                    Napi::HandleScope scope(info.Env());
                    if (!info[0].IsObject()) {
                        printf("Axios returned: %s\n",
                               info[0].ToString().Utf8Value().c_str());
                        return;
                    }
                    std::string data =
                        info[0].ToObject().Get("data").ToString().Utf8Value();
                    printf("Result is:\n\n%s\n", data.c_str());
                })});

            r.Get("catch").As<Napi::Function>().Call(
                r,
                {Napi::Function::New(env, [](const Napi::CallbackInfo &info) {
                    Napi::HandleScope scope(info.Env());
                    if (!info[0].IsNull()) {
                        printf("Axios error: %s",
                               info[0].As<Napi::Error>().what());
                        return;
                    }
                })});
            env.Run();
        } catch (const Napi::Error &e) {
            fprintf(stderr, "Caught a JS exception: %s\n", e.what());
        }
    } catch (napi_status r) {
        fprintf(stderr, "Failed initializing Node.js environment: %d\n",
                (int)r);
    }
    return 0;
}