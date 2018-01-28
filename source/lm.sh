#!/bin/bash

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=./ -G "Unix Makefiles" ../

make
