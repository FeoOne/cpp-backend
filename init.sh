#!/usr/bin/env bash

echo "Make library aliases..."

mkdir engine/include
cd engine/include
ln -s ../src ./engine
cd -

mkdir framework/include
cd framework/include
ln -s ../src ./framework
cd -
