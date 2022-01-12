#!/bin/bash

if [ ! -d tmp/linux ]; then
  mkdir -p tmp/linux
fi

cd tmp/linux
cmake ../..
make
# cp -rf wsjcpp-yaml ../
