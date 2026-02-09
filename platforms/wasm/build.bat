@REM Author: Chinthaka Senanayaka
@REM Year: 2025

cd platforms\wasm

@REM If you built the base WASM image on your local, run this file. Building this image takes 10 minutes.
docker build -t build-wasm-image:latest .
docker image tag build-wasm-image:latest wchinthakaps/build-wasm-image:2.0.0
docker push wchinthakaps/build-wasm-image:2.0.0

cd ..\..