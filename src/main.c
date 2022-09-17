//https://github.com/mmomtchev/libnode/blob/main/examples/axios-example-es6.cc
#include <stdio.h>
#define NAPI_EXPERIMENTAL
#define NAPI_EMBEDDING
#include <napi.h>

int main()
{
    try
    {
        Napi::Platform platform;
        Napi::PlatformEnv env(platform);

        try
        {
            Napi::HandleScope scope(env);

            Napi::Function import =
                env.Global().Get("import").As<Napi::Function>();

            Napi::Value axios_promise = import.MakeCallback(
                env.Global(), {Napi::String::New(env, "axios")});

            Napi::Object axios_import =
                axios_promise.As<Napi::Promise>().Await().ToObject();
            Napi::Object axios = axios_import.Get("default").ToObject();
//https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
            Napi::Promise r =
                axios.Get("post")//"get"
                    .As<Napi::Function>()
                    .Call({Napi::String::New(env, "https://www.google.com"),
                    Napi::String::New(env, "{
                        pageOffset: 0,
                        pageLength: 10,
                        postalCode: 77777
                    }").toObject(),
                    Napi::String::New(env, 
                    "{headers:{Authorization: Bearer "+API_TOKEN+"}}"
                    ).toObject()//https://developers.cloudflare.com/workers/platform/environment-variables/
        })//mastercard api + bearer auth
                    .As<Napi::Promise>();
        r.Get("then").As<Napi::Function>().Call(
            r,
            {Napi::Function::New(env, [](const Napi::CallbackInfo &info) {
                Napi::HandleScope scope(info.Env());
                if (!info[0].IsObject())
                {
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
                if (!info[0].IsNull())
                {
                    printf("Axios error: %s",
                           info[0].As<Napi::Error>().what());
                    return;
                }
            })});
        env.Run();
    }
    catch (const Napi::Error &e)
    {
        fprintf(stderr, "Caught a JS exception: %s\n", e.what());
    }
}
catch (napi_status r)
{
    fprintf(stderr, "Failed initializing Node.js environment: %d\n",
            (int)r);
}
return 0;
}