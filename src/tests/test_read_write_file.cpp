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
#include <sstream>
#include <fstream>
#include <wsjcpp_yaml.h>

int main() {
    std::string sFilepath = "../../../../src/tests/data-tests/read-write-file/docker-compose.yml";
    std::string sFilepathOutput = "../../../../src/tests/data-tests/read-write-file/docker-compose.output.yml";
    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;

    if (!yaml.getRoot()->hasElement("version")) {
        std::cerr << "Check failed: version" << std::endl;
        ret = -1;
    }
    if (!yaml.getRoot()->hasElement("volumes")) {
        std::cerr << "Check failed: volumes" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("networks")) {
        std::cerr << "Check failed: networks" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("services")) {
        std::cerr << "Check failed: services" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("version")->getValue() != "3") {
        std::cerr << "Check failed: version-value" << std::endl;
        ret = -1;
    }


    if (!yaml.saveToFile(sFilepathOutput, sError)) {
        std::cerr << "Error save: " << sError << std::endl;
        return -1;
    }

    std::ifstream f1(sFilepath.c_str());
    if (!f1) {
        std::cerr << "FAILED could not open file to read " << sFilepath << std::endl;
        return -1;
    }

    std::string sOriginalFileContent = std::string(
        (std::istreambuf_iterator<char>(f1)),
        std::istreambuf_iterator<char>()
    );

    std::ifstream f2(sFilepathOutput.c_str());
    if (!f2) {
        std::cerr << "FAILED could not open file to read " << sFilepathOutput << std::endl;
        return -1;
    }

    std::string sOutputFileContent = std::string(
        (std::istreambuf_iterator<char>(f2)),
        std::istreambuf_iterator<char>()
    );

    sOriginalFileContent += "\n"; // TODO fix
    if (sOutputFileContent != sOriginalFileContent) {
        std::cerr << "Check failed: not equal" << std::endl;
        ret = -1;
    }

    return ret;
}