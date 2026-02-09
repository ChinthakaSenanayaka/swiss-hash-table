# Building this image takes 10 minutes.
# Author: Chinthaka Senanayaka
# Year: 2025
FROM ubuntu:jammy

RUN apt-get update && apt-get -y upgrade
# Installing wget
RUN apt-get -y install wget curl python3 cmake git nodejs npm snapd firefox

RUN curl -sSf https://raw.githubusercontent.com/WasmEdge/WasmEdge/master/utils/install.sh | bash

RUN git clone https://github.com/emscripten-core/emsdk.git
RUN cd emsdk && git pull && chmod -R 777 .
RUN cd /emsdk && ./emsdk install 3.1.27 && ./emsdk activate 3.1.27