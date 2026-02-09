#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

cd platforms/intel

# If you built the base Intel image on your local, run this file. Building this image takes 10 minutes.
docker build -t build-intel-image:latest .
docker image tag build-intel-image:latest wchinthakaps/build-intel-image:2.0.0
docker push wchinthakaps/build-intel-image:2.0.0

cd ../..