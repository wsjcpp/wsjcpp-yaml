# wsjcpp-yaml

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp-yaml.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp-yaml) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-yaml.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-yaml) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-yaml.svg)](https://github.com/wsjcpp/wsjcpp-yaml) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-yaml.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-yaml/network/members) [![Total alerts](https://img.shields.io/lgtm/alerts/g/wsjcpp/wsjcpp-yaml.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-yaml/alerts/) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wsjcpp/wsjcpp-yaml.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-yaml/context:cpp)

C++ YAML parser/reader and writer of *.yaml/*.yml files with keeping user formatting 

## Integrate to your c++ project

include files:

- src/wsjcpp_yaml.cpp
- src/wsjcpp_yaml.h

or just

```
$ wsjcpp install https://github.com/wsjcpp/wsjcpp-yaml:master
```

## Example usage:

In you main file configure logger:

```cpp

#include <string.h>
#include <iostream>
#include "wsjcpp_yaml.h"

class MyLogger : public IWsjcppYamlLog {
    public:
        // IWsjcppYamlLog
        virtual void err(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [error] : " << sMessage << std::endl;
        };
        virtual void throw_err(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [critical_error] : " << sMessage << std::endl;
            throw std::runtime_error(TAG + " [critical_error] : " + sMessage);
        };
        virtual void warn(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [warn] : " << sMessage << std::endl;
        };
        virtual void info(const std::string &TAG, const std::string &sMessage) override {
            std::cout << TAG << " [info] : " << sMessage << std::endl;
        };
};

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    std::string appLogPath = ".logs";
    MyLogger *pLogger = new MyLogger();

    // now you can use WsjcppYaml
    WsjcppYaml yaml;
    yaml.setLogger(pLogger);
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
        yaml.throw_err(TAG, "Error parsing");
        return -1;
    }

    std::cout << "yaml is " << yaml["yaml1"].valStr() << std::endl;
    std::cout << "some-map is " << yaml["some-map"].valStr() << std::endl;
    std::cout << "some-map2 is " << yaml["some-map2"].valStr() << std::endl;
    std::cout << "some-array has " << std::to_string(yaml["some-array"].valStr()) << std::endl;
    std::cout << "some-array element 0 is " << yaml["some-array"][0].valStr() << std::endl;
    std::cout << "some-array element 1 is " << yaml["some-array"][1].valStr() << std::endl;
    std::cout << "some-am has " << std::to_string(yaml["some-am"].size()) << std::endl;
    std::cout << "some-am is array: " << (yaml["some-am"].isArray() ? "yes" : "no") << std::endl;
    std::cout << "some-am has comment " << yaml["some-am"].comment() << std::endl;
    std::cout << "some-am element 0 : p1 is  " << yaml["some-am"][0]["p1"].valStr() << std::endl;
    std::cout << "some-am element 0 : p2 is  " << yaml["some-am"][0]["p2"].valStr() << std::endl;
    std::cout << "some-am element 1 : p1 is  " << yaml["some-am"][1]["p1"].valStr() << std::endl;
    std::cout << "some-am element 1 : p2 is  " << yaml["some-am"][1]["p2"].valStr() << std::endl;

    return 0;
}

```
