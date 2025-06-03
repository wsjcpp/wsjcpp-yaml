#!/bin/bash

check_ret() {
    if [ $1 -ne 0 ]; then
        echo ""
        echo "!!! FAIL: $2"
        echo "********************************************************************************"
        echo ""
        exit $1
    else
        echo ""
        echo "*** SUCCESS: $2"
        echo "********************************************************************************"
        echo ""
    fi
}

# if [ ! -d tmp/linux_release ]; then
#   mkdir -p tmp/linux_release
# fi

cmake -H. -B./tmp/linux_release -DCMAKE_BUILD_TYPE=Release
check_ret $? "configure"

cmake --build ./tmp/linux_release --config Release
check_ret $? "build"

cd ./tmp/linux_release && ctest --output-on-failure
check_ret $? "tests"
