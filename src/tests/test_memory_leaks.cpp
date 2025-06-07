/*
MIT License

Copyright (c) 2019-2025 wsjcpp

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Official Source Code: https://github.com/wsjcpp/wsjcpp-yaml
*/

#include <iostream>
#include <wsjcpp_yaml.h>
#include "get_current_rss.h"
#include "process_mem_usage.h"

int createManyTimesObjects() {
    const std::string sFilepath = "../../../../src/tests/data-tests/for-memory-leak/some.yml";
    std::string sError;
    for (int i = 0; i < 10000; i++) {
        WsjcppYaml yaml;

        if (!yaml.loadFromFile(sFilepath, sError)) {
            std::cerr << sError << std::endl;
            return -1;
        }
    }
    return 0;
}

int main() {
    double nBeforeVm, nBeforeRss;

    // first use for memory alloc memory for work
    if (createManyTimesObjects() != 0) {
        return -1;
    }

    process_mem_usage(nBeforeVm, nBeforeRss);
    if ((int)nBeforeVm <= 0) {
        std::cerr << "memory vm could not be null" << std::endl;
        return -1;
    }
    if ((int)nBeforeRss <= 0) {
        std::cerr << "memory rss could not be null" << std::endl;
        return -1;
    }

    // code again check the memoty leak
    if (createManyTimesObjects() != 0) {
        return -1;
    }

    double nAfterVm, nAfterRss;

    process_mem_usage(nAfterVm, nAfterRss);

    std::cerr << "memory vm before " << nBeforeVm << ", after " << nAfterVm << std::endl;
    std::cerr << "memory rss before " << nBeforeRss << ", after " << nAfterRss << std::endl;

    if ((int)nBeforeVm != (int)nAfterVm) {
        std::cerr << "memory leak found by vm" << std::endl;
        return -1;
    }
    if ((int)nBeforeRss != (int)nAfterRss) {
        std::cerr << "memory leak found by rss" << std::endl;
        return -1;
    }

    return 0;
}