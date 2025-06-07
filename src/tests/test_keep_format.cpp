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
    // https://github.com/wsjcpp/wsjcpp-yaml/issues/29

    std::string sInput =
        "# commet1:\n"
        "\n"
        "val1: 1\n"
        "\n"
        "unit-tests:\n"
        "  cases:\n"
        "    - name: \"NormalizeUnitTestName\"\n"
        "      description: \"Test Normalize UnitTest Name\"\n"
        "    - name: \"generateFilenameForUnitTest\"\n"
        "      description: \"Test generate filename for UnitTest\"\n"
        "    - name: \"InitPackage\"\n"
        "      description: \"Test for init package\"\n"
        "      enabled: \"no\"\n"
        "\n"
        "    - name: \"ReadPackage\"\n"
        "      description: \"Test for read package\"\n"
        "\n"
        "\n"
        "resources:\n"
        "  - filepath: \"./build_simple.sh\"\n"
        "    filesize: 77\n"
        "    pack-as: \"binary\"\n"
        "    modified: 1600401759\n"
        "    sha1: \"\"\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("input.yml", sInput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    std::string sOutput = "";
    if (!yaml.saveToString(sOutput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    if (sOutput != sInput) {
        std::cerr << "sOutput != sInput" << std::endl;
        return -1;
    }

    // try again

    if (!yaml.loadFromString("output.yml", sOutput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    sOutput = "";
    if (!yaml.saveToString(sOutput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    if (sOutput != sInput) {
        std::cerr << "sOutput != sInput (2)" << std::endl;
        return -1;
    }
    return 0;
}