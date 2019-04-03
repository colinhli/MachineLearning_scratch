#!/bin/sh
mkdir build
cd build
cmake ../ -D-DCMAKE_INSTALL_PREFIX=`pwd`/../../build