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
#include <cfloat>
#include <wsjcpp_yaml.h>
#include "helpers.h"

int main() {
    std::string sFilepath = find_test_data_file("data/float-double/example.yml");

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;
    if (!yaml.getRoot()->hasElement("float")) {
        std::cerr << "Parameter 'float' not found" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("float")) {
        std::cerr << "Parameter 'float' has not value" << std::endl;
        ret = -1;
    }

    std::string value_float = yaml["float"];

    std::string expected_val_str = "1.0001";
    if (value_float != expected_val_str) {
        std::cerr << "Parameter 'float' has value '" << value_float << "', but expected '" << expected_val_str << "'" << std::endl;
        ret = -1;
    }

    float val_float = yaml["float"].valFloat();
    float expected_float = 1.0001f;
    if (abs(val_float - expected_float) > FLT_EPSILON) {
        std::cerr << "Parameter 'float' has value '" << val_float << "', but expected '" << expected_float << "'" << std::endl;
        ret = -1;
    }

    return ret;
}
