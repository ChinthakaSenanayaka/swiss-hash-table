#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

cd platforms/riscv

# If you built the base RISCV image on your local, run this file. Building this image takes 3 hours.
# *** WARNING: This image on Docker Hub is compressed by Docker Engine and it is 5.75GB.
# *** After extracting to local it will take 16.5GB.
# *** Therefore, local Dcoker Engine's settings' resources should be at least 20GB.
docker build -t build-riscv-image:latest .
docker image tag build-riscv-image:latest wchinthakaps/build-riscv-image:2.0.0
docker push wchinthakaps/build-riscv-image:2.0.0

cd ../..