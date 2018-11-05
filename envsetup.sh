#!/usr/bin/env bash

EXTERNAL_DIR="external"

mkdir -p ${EXTERNAL_DIR}
mkdir -p modules/manbtc/${EXTERNAL_DIR}

if [ ! -d ${EXTERNAL_DIR}/jemalloc ]; then
    echo "Setting up jemalloc..."
    cd ${EXTERNAL_DIR}
    git clone https://github.com/jemalloc/jemalloc.git jemalloc
    cd jemalloc
    ./autogen.sh --with-jemalloc-prefix="je_" --without-export --enable-debug --disable-cxx
    make dist
    make -j 4
    cd ../..
fi

if [ ! -d modules/manbtc/${EXTERNAL_DIR}/bitcoin ]; then
    echo "Setting up bitcoin..."
    brew install -y automake berkeley-db4 libtool boost miniupnpc openssl pkg-config protobuf python qt libevent qrencode
    cd modules/manbtc/${EXTERNAL_DIR}
    git clone https://github.com/bitcoin/bitcoin.git bitcoin
    cd bitcoin
    ./autogen.sh
    ./configure
    make -j 4
    cd ../../../..
fi
