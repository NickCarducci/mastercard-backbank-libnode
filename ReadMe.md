a. [libnode v8 worker proper](https://github.com/nodejs/node/issues/23265#issuecomment-1236078047)

i. [worker-emscripten-template](https://github.com/cloudflare/worker-emscripten-template/blob/master/webpack.config.js)

# Why? *Of course, to hide [our service api](https://developer.mastercard.com/product/location-intelligence#resources) bearer token from caller*

1. *Dependencies*: Cloudflare service workers use v8 js engine not nodejs. (*first make the nodejs into a c language op*)

## [Node](https://github.com/nodejs/node/blob/main/BUILDING.md#building-nodejs-on-supported-platforms) source ([js_native_api_v8.cc](https://github.com/mmomtchev/node/blob/napi-libnode/src/js_native_api_v8.cc) napi-libnode branch)

`git clone -b napi-libnode https://github.com/mmomtchev/node.git`

`cd node && ./configure --shared && make -j4` (this takes 10-15 minutes)

`git clone -b napi_embedding https://github.com/mmomtchev/node-addon-api.git`

~~`chmod +x make-libnode-dist.sh`~~

`brew install wget`

`./extract-libnode-dist.sh`

`-I` [include](https://stackoverflow.com/questions/31026829/trying-to-use-i-option-with-g)

`g++ -v -I usr/include/libnode -I $(pwd)/node -I $(pwd)/node-addon-api -o libnode-napi src/main.cc -lnode` 

[~~`$PATH:$HOME`~~](https://cplusplus.com/forum/unices/71641/)

[`g++ -B /napi.h `](https://unix.stackexchange.com/questions/523350/assign-pwd-to-path-variable-conditionally)

2. ~~... should I reattempt a *hard coded* bearer token in a [rust wasm bindgen jsfuture service worker](https://github.com/NickCarducci/mastercard-backbank/blob/maintenance/lib.rs)~~

> "What about [service Workers Example](https://community.cloudflare.com/t/how-to-call-api-using-cloudflare/408641): Modify request property"? (durable object, otherwise just for KeyValue store?) zero trust would possibly [redirect: follow](https://community.cloudflare.com/t/ip-address-of-cloudflare-pages/380083/9)

> ["Native" Workers support with fetch](https://blog.cloudflare.com/workers-rust-sdk/)

ii. [rustwasm-worker-template](https://github.com/cloudflare/rustwasm-worker-template)

`wrangler publish`

b. [mastercard-backbank-node-zero-trust](https://github.com/NickCarducci/mastercard-backbank-node-zero-trust)
