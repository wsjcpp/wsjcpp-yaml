
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

#pragma once

#include <string>
#include <fstream>

#if defined(_WIN32)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

static std::string find_test_data_file(const std::string &sFilePath) {
    char buff[FILENAME_MAX];
    char *path = GetCurrentDir(buff, FILENAME_MAX);
    if (path == NULL) {
        std::cerr << "ERROR: Could not get current directory path" << std::endl;
        return "did_not_found_file: " + sFilePath;
    }
    std::cout << "Current path: " << buff << std::endl;

    std::string sRet = "../../src/tests/" + sFilePath;

    // find path
    for (int i = 0; i < 5; i++) {
        std::ifstream file_(sRet.c_str());
        if (!file_) {
            sRet = "../" + sRet;
        } else {
            return sRet;
        }
    }
    return sFilePath;
}
