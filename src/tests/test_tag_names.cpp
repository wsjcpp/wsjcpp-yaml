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

int main() {
    std::string sTestYaml = "./test10: one";
    WsjcppYaml yaml;
    std::string sError;
    int ret = 0;
    if (yaml.loadFromString("wrong name", "./test10: one", sError)) {
        std::cerr << "Failed check 'wrong name'" << std::endl;
        ret = -1;
    }

    if (!yaml.loadFromString("name use quotes", "\"./test10\": one", sError)) {
        std::cerr << "Failed check 'name use quotes 1'" << std::endl;
        ret = -1;
    }

    if (yaml.loadFromString("name use quotes", "\"./te\"st10\": one", sError)) {
        std::cerr << "Failed check 'name use quotes 2 - wrong'" << std::endl;
        ret = -1;
    }

    if (!yaml.loadFromString("name use quotes", "\"./te\\\"st10\": one", sError)) {
        std::cerr << "Failed check 'name use quotes 3'" << std::endl;
        ret = -1;
    }

    if (!yaml.loadFromString("array",
        "arr1: \n"
        "  - ./te:11\n"
        "  - \"./te\":11\n"
    , sError)) {
        std::cerr << "Failed check 'array'" << std::endl;
        ret = -1;
    };

    if (!yaml.getRoot()->getElement("arr1")->isArray()) {
        std::cerr << "Failed check 'arr1 is array'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("arr1")->getLength() != 2) {
        std::cerr << "Failed check 'arr1 size 2'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->getElement("arr1")->getElement(0)->isValue()) {
        std::cerr << "Failed check 'arr1 el 0 is value'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("arr1")->getElement(0)->getValue() != "./te:11") {
        std::cerr << "Failed check 'arr1 el 0 is value'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->getElement("arr1")->getElement(1)->isMap()) {
        std::cerr << "Failed check 'arr1 el 1 is map'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->getElement("arr1")->getElement(1)->hasElement("./te")) {
        std::cerr << "Failed check 'arr1 el 1 is map'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("arr1")->getElement(1)->getElement("./te")->getValue() != "11") {
        std::cerr << "Failed check 'arr1 el 1 is map'" << std::endl;
        ret = -1;
    }

    return ret;
}