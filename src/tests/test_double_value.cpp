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

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <wsjcpp_yaml.h>

#if defined(_WIN32)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

int main() {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX );
    std::cout << "Current path: " << buff << std::endl;
    std::string sFilepath = "../../../src/tests/data/float-double/example.yml";
    // find path
    {
        std::ifstream file_(sFilepath.c_str());
        if (!file_) {
            sFilepath = "../" + sFilepath;
        }
    }
    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;
    if (!yaml.getRoot()->hasElement("double")) {
        std::cerr << "Parameter 'float' not found" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("double")) {
        std::cerr << "Parameter 'double' has not value" << std::endl;
        ret = -1;
    }

    std::string expected_val_str = "1.0002";
    if (yaml.getRoot()->getElement("double")->getValue() != expected_val_str) {
        std::cerr << "Parameter 'double' has value string '" << yaml.getRoot()->getElement("double")->getValue() << "', but expected '" << expected_val_str << "'" << std::endl;
        ret = -1;
    }

    double val_double = yaml["double"].valDouble();
    double expected_double = 1.0002f;
    // std::numeric_limits<double>::epsilon() => 2.22045e-16
    // std::numeric_limits<float>::epsilon() => 1.19209e-07
    // abs(val_double - expected_double) => 3.31879e-08
    if (abs(val_double - expected_double) > std::numeric_limits<float>::epsilon()) {
        std::cerr << "Parameter 'double' has value number '" << val_double << "', but expected '" << expected_double << "'" << std::endl;
        ret = -1;
    }

    yaml["double"].val(1.0003f);

    expected_val_str = "1.0003";
    if (yaml.getRoot()->getElement("double")->getValue() != expected_val_str) {
        std::cerr << "Parameter 'double' has value string '" << yaml.getRoot()->getElement("double")->getValue() << "', but expected '" << expected_val_str << "'" << std::endl;
        ret = -1;
    }

    expected_double = 1.0003f;
    val_double = yaml["double"].valDouble();
    if (abs(val_double - expected_double) > std::numeric_limits<float>::epsilon()) {
        std::cerr << "Parameter 'double' has value number '" << val_double << "', but expected '" << expected_double << "'" << std::endl;
        ret = -1;
    }
    float val_double_like_float = yaml["double"].valFloat();
    float expected_float = 1.0003f;
    if (abs(val_double_like_float - expected_float) > std::numeric_limits<float>::epsilon()) {
        std::cerr << "Parameter 'double' has value number (like float) '" << val_double_like_float << "', but expected '" << expected_float << "'" << std::endl;
        ret = -1;
    }

    // compareD("has double value is 1.0003 (double 2)", yaml["double"].valDouble(), 1.0003f);

    return ret;
}