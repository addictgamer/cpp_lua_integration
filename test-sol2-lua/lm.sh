#!/bin/bash

mkdir build
cd build

export LUAJIT_DIR="/usr/include/luajit-2.0/"

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=./ -G "Unix Makefiles" ../

make
