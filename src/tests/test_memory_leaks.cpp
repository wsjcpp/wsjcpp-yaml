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