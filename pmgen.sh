#!/usr/bin/env bash

mkdir -p ./message/generated/
./cmake-build-debug/tools/pmgen/pmgen -i ./message/schema/backend_database.pro -o ./message/generated/
