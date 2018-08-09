#!/usr/bin/env bash

echo "Make library aliases..."

mkdir engine/include
ln -s engine/src engine/include/engine

mkdir framework/include
ln -s framework/src framework/include/framework
