//https://github.com/mmomtchev/libnode/blob/main/examples/axios-example-es6.cc
#include <stdio.h>
#define NAPI_EXPERIMENTAL
#define NAPI_EMBEDDING
#include <napi.h>

int main()
{
    try
    {
        Napi::Platform platform; ////https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
        Napi::PlatformEnv env(platform);
        try
        {
            //Napi::Function dependency =
                //env.Global().Get("require").As<Napi::Function>().Call({Napi::String::New(env, "./dependency.js")}).As<Napi::Function>();

            Napi::HandleScope scope(env);
            env.Global().Get("import").As<Napi::Function>().MakeCallback(
                                                               env.Global(), {Napi::String::New(env, "axios")}) //Value
                .As<Napi::Promise>()
                .Await()
                .ToObject() //Object
                .Get("default")
                .ToObject()  //Object
                .Get("post") //"get"
                .As<Napi::Function>()
                .Call({
                    Napi::String::New(env, "https://www.google.com"),
                    Napi::String::New(env,
                                      "{pageOffset: 0,pageLength: 10,postalCode: 77777}")
                        .toObject(),
                    Napi::String::New(env,
                                      "{headers:{Authorization: Bearer " + API_TOKEN + "}}")
                        .toObject()  //https://developers.cloudflare.com/workers/platform/environment-variables/
                })                   //mastercard api + bearer auth
                .As<Napi::Promise>() //Promise
                .Get("then")
                .As<Napi::Function>()
                .Call(
                    response,
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
                        return response;
                    })})
                .Get("catch")
                .As<Napi::Function>()
                .Call(response, {Napi::Function::New(env, [](const Napi::CallbackInfo &info) {
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
    catch (napi_status response)
    {
        fprintf(stderr, "Failed initializing Node.js environment: %d\n",
                (int)response);
    }
    return 0;
}