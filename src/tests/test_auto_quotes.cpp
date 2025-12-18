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
    // https://github.com/wsjcpp/wsjcpp-yaml/issues/24

    std::string sInput =
        "# commet1:\n"
        "val1: 1\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("input.yml", sInput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    yaml["val1"].val("some\nsome");
    yaml.getRoot()->setElementValue("v\ng", "opa\ndone");

    std::string sOutput = "";
    if (!yaml.saveToString(sOutput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    std::string sExpected =
        "# commet1:\n"
        "val1: \"some\\nsome\"\n"
        "\"v\\ng\": \"opa\\ndone\"\n"
    ;

    if (sOutput != sExpected) {
        std::cerr << "sOutput != sExpected" << std::endl;
        std::cerr << "Got: \n----\n" << sOutput << "\n------\nExpected\n-----\n" << sExpected << "\n------\n" << std::endl;
        return -1;
    }
    return 0;
}