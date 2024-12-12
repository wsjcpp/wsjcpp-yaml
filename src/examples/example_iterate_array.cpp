/*
MIT License

Copyright (c) 2019-2024 wsjcpp

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

void example_iterate_array() {

    std::string sTest =
        "'2021-10-08':\n"
        "  - code: '300209'\n"
        "    focusstr: ''\n"
        "  - code: '300047'\n"
        "    focusstr: ''\n"
        "  - code: '300970'\n"
        "    focusstr: ''\n"
        "  - code: '300288'\n"
        "    focusstr: ''\n"
        "'2021-10-11':\n"
        "  - code: '300162'\n"
        "    focusstr: ''\n"
        "  - code: '300209'\n"
        "    focusstr: ''\n"
        "  - code: '300972'\n"
        "    focusstr: ''\n"
        "  - code: '300159'\n"
        "    focusstr: ''\n"
    ;

    WsjcppYaml yaml2;
    std::string sError;
    if (!yaml2.loadFromString("test", sTest, sError)) {
        std::cerr << sError.c_str() << std::endl;
        return;
    }
    WsjcppYamlCursor cur = yaml2.getCursor();
    std::vector<std::string> vKeys = cur.keys();
    for (unsigned int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        int nCount = cur[sKey].size(); // musts array
        for (int n = 0; n < nCount; n++) {
            WsjcppYamlCursor el = cur[sKey][n];
            std::cout
                << "code = " << el["code"].valInt()
                << "; focusstr = " << el["focusstr"].valStr().c_str()
                << ";"
                << std::endl;
        }
    }
}