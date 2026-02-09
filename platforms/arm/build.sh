#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

cd platforms/arm

# If you built the base ARM image on your local, run this file. Building this image takes 1 hour.
docker build -t build-arm-image:latest .
docker image tag build-arm-image:latest wchinthakaps/build-arm-image:2.0.0
docker push wchinthakaps/build-arm-image:2.0.0

cd ../..