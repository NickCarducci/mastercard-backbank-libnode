[libnode v8 worker proper](https://github.com/nodejs/node/issues/23265#issuecomment-1236078047)

[worker-emscripten-template](https://github.com/cloudflare/worker-emscripten-template/blob/master/webpack.config.js)

# Why?

1. Cloudflare service workers use v8 js engine not nodejs. (*first make the nodejs into a c language op*)

~~2.~~ ... should I reattempt a *hard coded* bearer token in a [rust wasm bindgen jsfuture service worker](https://github.com/NickCarducci/mastercard-backbank/blob/maintenance/lib.rs)

[rustwasm-worker-template](https://github.com/cloudflare/rustwasm-worker-template)