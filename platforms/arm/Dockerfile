# Building this image takes 1 hour.
# Author: Chinthaka Senanayaka
# Year: 2025
FROM ubuntu:jammy

RUN apt-get update && apt-get -y upgrade
# Installing ARM GCC compiler
RUN apt-get -y install gcc-arm-none-eabi
#Install ARM QEMU emulator
RUN apt-get -y install qemu qemu-user-static qemu-system-arm