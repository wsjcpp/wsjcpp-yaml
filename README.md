# wsjcpp-yaml

[![Build Status](https://api.travis-ci.org/wsjcpp/wsjcpp-yaml.svg?branch=master)](https://api.travis-ci.org/wsjcpp/wsjcpp-yaml) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-yaml.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-yaml/stargazers) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-yaml.svg)](https://github.com/wsjcpp/wsjcpp-yaml/) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-yaml.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-yaml/network/members)

C++ Write/Reader yaml files


## Integrate to your c++ project

include files:

- src/wsjcpp_yaml.cpp
- src/wsjcpp_yaml.h
- src.wsjcpp/wsjcpp-core/wsjcpp_core.h
- src.wsjcpp/wsjcpp-core/wsjcpp_core.cpp

In you main file configure logger:

```cpp

#include <string.h>
#include <iostream>
#include "wsjcpp_yaml.h"
#include "wsjcpp_core.h"


int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    std::string appLogPath = ".logs";
    WSJCppLog::setLogDirectory(appLogPath);
    if (!WSJCppCore::dirExists(appLogPath)) {
        WSJCppCore::makeDir(appLogPath);
    }
    WSJCppLog::info(TAG, "Hello!");

    // now you can use WSJCppYAML
    WSJCppYAML yaml;
    if (yaml.loadFromString(
        "# yaml content\n"
        "yaml: nice format\n"
        "some-map: value1\n"
        "some-map2: value2\n"
        "some-array:\n"
        "  - test1 \n"
        "  - test2 \n"
    )) {
        WSJCppLog::throw_err(TAG, "Error parsing");
        return -1;
    }

    std::cout << "yaml is " << yaml.getRoot()->getElement("yaml")->getValue() << std::endl;
    std::cout << "some-map is " << yaml.getRoot()->getElement("some-map")->getValue() << std::endl;
    std::cout << "some-map2 is " << yaml.getRoot()->getElement("some-map2")->getValue() << std::endl;
    std::cout << "some-array has " << std::to_string(yaml.getRoot()->getElement("some-array")->getLength()) << std::endl;
    std::cout << "some-array element 1 is " << yaml.getRoot()->getElement("some-array")->->getElement(0)->getValue() << std::endl;
    std::cout << "some-array element 2 is " << yaml.getRoot()->getElement("some-array")->->getElement(1)->getValue() << std::endl;
    return 0;
}

```