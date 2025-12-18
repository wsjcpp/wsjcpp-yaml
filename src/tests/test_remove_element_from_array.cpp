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
#include "helpers.h"

int main() {
    std::string sFilepath = find_test_data_file("data/remove-element-from-array.yml");

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;

    WsjcppYamlNode *pArr1 = yaml.getRoot()->getElement("arr1");
    if (pArr1->getLength() != 4) {
        std::cerr << "Check failed: arr1 len" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(0)->getElement("name")->getValue() != "i1") {
        std::cerr << "Check failed: arr1 name0" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(1)->getElement("name")->getValue() != "i2") {
        std::cerr << "Check failed: arr1 name1" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(2)->getElement("name")->getValue() != "i3") {
        std::cerr << "Check failed: arr1 name2" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(3)->getValue() != "very different array items type") {
        std::cerr << "Check failed: arr1 name3" << std::endl;
        ret = -1;
    }

    pArr1->removeElement(1);

    if (pArr1->getLength() != 3) {
        std::cerr << "Check failed: arr1 len (2)" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(0)->getElement("name")->getValue() != "i1") {
        std::cerr << "Check failed: arr1 name0 (2)" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(1)->getElement("name")->getValue() != "i3") {
        std::cerr << "Check failed: arr1 name1 (2)" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(2)->getValue() != "very different array items type") {
        std::cerr << "Check failed: arr1 name2 (2)" << std::endl;
        ret = -1;
    }

    return ret;
}
