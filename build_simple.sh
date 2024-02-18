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

if [ ! -d tmp/linux ]; then
  mkdir -p tmp/linux
fi

cmake -H. -B./tmp/linux_release -DCMAKE_BUILD_TYPE=Release
check_ret $? "configure"

cmake --build ./tmp/linux_release --config Release
check_ret $? "build"


cd ./tmp/release && ctest --output-on-failure

cd ./unit-tests.wsjcpp
./unit-tests
check_ret $? "wsjcpp.unit-tests"
cd ..

./yamlcpp_tests
check_ret $? "gtests"
