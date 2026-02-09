# Building this image takes 3 hours.
# Author: Chinthaka Senanayaka
# Year: 2025
FROM ubuntu:jammy

RUN apt-get update && apt-get -y upgrade
# Installing wget
RUN apt-get -y install wget

# Installing RISCV GCC compiler
RUN apt-get -y  install autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build git cmake libglib2.0-dev

# Build RISCV Vector Extension on the Docker image
ENV RISCV /opt/riscv
RUN mkdir -p $RISCV

ENV RISCV_SRCS /home/riscv_srcs/
RUN mkdir -p $RISCV_SRCS

ENV PATH $RISCV/bin:$PATH

WORKDIR $RISCV_SRCS
RUN git clone https://github.com/riscv/riscv-gnu-toolchain
WORKDIR $RISCV_SRCS/riscv-gnu-toolchain
RUN ./configure --prefix=$RISCV --enable-multilib 
RUN make
RUN make build-qemu
RUN make install

RUN rm -r $RISCV_SRCS
