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
    std::string sTestYaml1 =
        "# Some comment 1\n"
        "test10: one\n"
        "test20: two # some comment 2\n"
    ;

    std::string sTestYaml2 =
        "# Some comment 1\n"
        "test11: one\n"
        "test20: two # some comment 2\n"
        "test22: two # some comment 2\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    int ret = 0;

    if (!yaml.loadFromString("parse1", sTestYaml1, sError)) {
        std::cerr << "Error parsing 1 " << sError << std::endl;
        return -1;
    }

    if (!yaml.getRoot()->hasElement("test10")) {
        std::cerr << "Failed check '(1) has test10'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->hasElement("test11")) {
        std::cerr << "Failed check '(1) has test11'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("test20")) {
        std::cerr << "Failed check '(1) has test20'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->hasElement("test22")) {
        std::cerr << "Failed check '(1) has test22'" << std::endl;
        ret = -1;
    }

    // 2

    if (!yaml.loadFromString("parse2", sTestYaml2, sError)) {
        std::cerr << "Error parsing 2 " << sError << std::endl;
        return -1;
    }

    if (yaml.getRoot()->hasElement("test10")) {
        std::cerr << "Failed check '(2) has test10'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("test11")) {
        std::cerr << "Failed check '(2) has test11'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("test20")) {
        std::cerr << "Failed check '(2) has test20'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("test22")) {
        std::cerr << "Failed check '(2) has test22'" << std::endl;
        ret = -1;
    }

    // 3

    yaml.clear();

    if (yaml.getRoot() != nullptr) {
        std::cerr << "Failed check '(3) has root'" << std::endl;
        ret = -1;
    }

    return ret;
}