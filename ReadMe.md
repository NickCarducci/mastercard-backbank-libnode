a. [libnode v8 worker proper](https://github.com/nodejs/node/issues/23265#issuecomment-1236078047)

i. [worker-emscripten-template](https://github.com/cloudflare/worker-emscripten-template/blob/master/webpack.config.js)

# Why? *Of course, to hide [our service api](https://developer.mastercard.com/product/location-intelligence#resources) bearer token from caller*

1. *Dependencies*: Cloudflare service workers use v8 js engine not nodejs. (*first make the nodejs into a c language op*)

2. ~~... should I reattempt a *hard coded* bearer token in a [rust wasm bindgen jsfuture service worker](https://github.com/NickCarducci/mastercard-backbank/blob/maintenance/lib.rs)~~

> "What about [service Workers Example](https://community.cloudflare.com/t/how-to-call-api-using-cloudflare/408641): Modify request property"? (durable object, otherwise just for KeyValue store?) zero trust would possibly [redirect: follow](https://community.cloudflare.com/t/ip-address-of-cloudflare-pages/380083/9)

> ["Native" Workers support with fetch](https://blog.cloudflare.com/workers-rust-sdk/)

ii. [rustwasm-worker-template](https://github.com/cloudflare/rustwasm-worker-template)

([js_native_api_v8.cc](https://github.com/mmomtchev/node/blob/napi-libnode/src/js_native_api_v8.cc) napi-libnode branch)
````
git clone -b napi-libnode https://github.com/mmomtchev/node.git
cd node && ./configure --shared && make -j4
````
~~`chmod +x make-libnode-dist.sh`~~

`g++ -I/usr/include/libnode -I/usr/include/node -o libnode-napi src/main.cc -lnode`

`wrangler publish`

b. [mastercard-backbank-node-zero-trust](https://github.com/NickCarducci/mastercard-backbank-node-zero-trust)
