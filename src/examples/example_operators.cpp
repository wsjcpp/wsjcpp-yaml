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

#include "examples.h"

#include "wsjcpp_yaml.h"

void example_operator_1() {

    std::string sTest =
        "test: 'string'\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("test", sTest, sError)) {
        std::cerr << sError.c_str() << std::endl;
        return;
    }
    WsjcppYamlCursor cur = yaml.getCursor();
    std::cout << "before : " << cur["test"].valStr().c_str() << std::endl;
    cur["test"] = "some new string";
    std::cout << "after 1 : " << cur["test"].valStr().c_str() << std::endl;
    cur["test"] = 111;
    std::cout << "after 2 : " << cur["test"].valStr().c_str() << std::endl;
    cur["test"] = true;
    std::cout << "after 3 : " << cur["test"].valStr().c_str() << std::endl;
}