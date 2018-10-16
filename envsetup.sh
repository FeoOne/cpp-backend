#!/usr/bin/env bash

EXTERNAL_DIR="3rdparty"

mkdir -p ${EXTERNAL_DIR}

if [ ! -d ${EXTERNAL_DIR}/jemalloc ]; then
    echo "Setting up jemalloc..."
    cd ${EXTERNAL_DIR}
    git clone https://github.com/jemalloc/jemalloc.git
    cd jemalloc
    ./autogen.sh --with-jemalloc-prefix="je_" --without-export --enable-debug --disable-cxx
    make dist
    make -j 4
    cd -
fi
