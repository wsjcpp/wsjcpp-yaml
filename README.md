# wsjcpp-yaml

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp-yaml.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp-yaml) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-yaml.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-yaml) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-yaml.svg)](https://github.com/wsjcpp/wsjcpp-yaml) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-yaml.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-yaml/network/members) [![Total alerts](https://img.shields.io/lgtm/alerts/g/wsjcpp/wsjcpp-yaml.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-yaml/alerts/) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wsjcpp/wsjcpp-yaml.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-yaml/context:cpp)

C++ Write/Reader yaml files


## Integrate to your c++ project

include files:

- src.wsjcpp/wsjcpp_core/wsjcpp_core.h
- src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp
- src/wsjcpp_yaml.cpp
- src/wsjcpp_yaml.h

In you main file configure logger:

```cpp

#include <string.h>
#include <iostream>
#include "wsjcpp_yaml.h"
#include "wsjcpp_core.h"


int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    std::string appLogPath = ".logs";
    WsjcppLog::setLogDirectory(appLogPath);
    if (!WsjcppCore::dirExists(appLogPath)) {
        WsjcppCore::makeDir(appLogPath);
    }
    WsjcppLog::info(TAG, "Hello!");

    // now you can use WsjcppYaml
    WsjcppYaml yaml;
    if (yaml.loadFromString(
        "# yaml content\n"
        "yaml1: nice format\n"
        "some-map: value1\n"
        "some-map2: value2\n"
        "some-array:\n"
        "  - test1 \n"
        "  - test2 \n"
        "some-am: # array + map element \n"
        "  - p1: v1 \n"
        "    p2: v2 \n"
        "  - p1: v3 \n"
        "    p2: v4 \n"
        "param2: 111\n"
    )) {
        WsjcppLog::throw_err(TAG, "Error parsing");
        return -1;
    }

    std::cout << "yaml is " << yaml["yaml1"].getValue() << std::endl;
    std::cout << "some-map is " << yaml["some-map"].getValue() << std::endl;
    std::cout << "some-map2 is " << yaml["some-map2"].getValue() << std::endl;
    std::cout << "some-array has " << std::to_string(yaml["some-array"].getLength()) << std::endl;
    std::cout << "some-array element 0 is " << yaml["some-array"][0].getValue() << std::endl;
    std::cout << "some-array element 1 is " << yaml["some-array"][1].getValue() << std::endl;
    std::cout << "some-am has " << std::to_string(yaml["some-am"].getLength()) << std::endl;
    std::cout << "some-am is array: " << (yaml["some-am"].isArray() ? "yes" : "no") << std::endl;
    std::cout << "some-am has comment " << yaml["some-am"].getComment() << std::endl;
    std::cout << "some-am element 0 : p1 is  " << yaml["some-am"][0]["p1"].getValue() << std::endl;
    std::cout << "some-am element 0 : p2 is  " << yaml["some-am"][0]["p2"].getValue() << std::endl;
    std::cout << "some-am element 1 : p1 is  " << yaml["some-am"][1]["p1"].getValue() << std::endl;
    std::cout << "some-am element 1 : p2 is  " << yaml["some-am"][1]["p2"].getValue() << std::endl;

    return 0;
}

```
