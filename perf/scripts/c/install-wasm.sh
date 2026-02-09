#!/bin/bash

mkdir -p ./build/wasm/

curl -sSf https://raw.githubusercontent.com/WasmEdge/WasmEdge/master/utils/install.sh | bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
chmod -R 777 .
./emsdk install 3.1.27
./emsdk activate 3.1.27
source $HOME/.wasmedge/env
. ./emsdk_env.sh