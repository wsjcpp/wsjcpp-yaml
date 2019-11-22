#!/bin/bash

if [ ! -d tmp ]; then
	mkdir -p tmp
fi

cd tmp
cmake ..
make
# cp -rf wsjcpp-yaml ../
