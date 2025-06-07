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
    std::string sTestYaml =
        "# Some comment 1\n"
        "param1: \"value1\" # v1\n"
        "param2: \" #$!!!value2\" # val 2\n"
        "\" param3 olala\" : val 3 # val 3*** \n"
        "param4: ' #$!!!value4' # val 4\n"
        "'param5 aha': ' #$!!!value5' # val 5\n"
        "url: \"https://github.com/wsjcpp/wsjcpp-yaml\"\n"
        "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues\n"
        "empty: \"\"\n"
        "array:\n"
        "  - \"https://github.com/wsjcpp/wsjcpp-core:v0.0.1\"\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("parse_quotes", sTestYaml, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;

    // TODO: .findLine(0)

    if (yaml.getRoot()->getElement("param1")->getValue() != "value1") {
        std::cerr << "Check failed: param1" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param1")->getComment() != "v1") {
        std::cerr << "Check failed: param1-comment" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param2")->getValue() != " #$!!!value2") {
        std::cerr << "Check failed: param2" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param2")->getComment() != "val 2") {
        std::cerr << "Check failed: param2-comment" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement(" param3 olala")->getValue() != "val 3") {
        std::cerr << "Check failed: param3 olala" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement(" param3 olala")->getComment() != "val 3***") {
        std::cerr << "Check failed: param3 olala comment" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param4")->getValue() != " #$!!!value4") {
        std::cerr << "Check failed: param4 val" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param4")->getComment() != "val 4") {
        std::cerr << "Check failed: param4 val" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("url")->getValue() != "https://github.com/wsjcpp/wsjcpp-yaml") {
        std::cerr << "Check failed: param4 url-value" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("issues")->getValue() != "https://github.com/wsjcpp/wsjcpp-yaml/issues") {
        std::cerr << "Check failed: param4 issues-value" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("empty")->getValue() != "") {
        std::cerr << "Check failed: param4 empty-value" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("array")->getElement(0)->getValue() != "https://github.com/wsjcpp/wsjcpp-core:v0.0.1") {
        std::cerr << "Check failed: array-element0-value" << std::endl;
        ret = -1;
    }

    std::string sSaved = "";
    if (!yaml.saveToString(sSaved, sError)) {
        std::cerr << "Error save: " << sError << std::endl;
        return -1;
    }
    std::string sExpected =
        "# Some comment 1\n"
        "param1: \"value1\" # v1\n"
        "param2: \" #$!!!value2\" # val 2\n"
        "\" param3 olala\": val 3 # val 3***\n"
        "param4: ' #$!!!value4' # val 4\n"
        "'param5 aha': ' #$!!!value5' # val 5\n"
        "url: \"https://github.com/wsjcpp/wsjcpp-yaml\"\n"
        "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues\n"
        "empty: \"\"\n"
        "array:\n"
        "  - \"https://github.com/wsjcpp/wsjcpp-core:v0.0.1\"\n"
    ;
    if (sSaved != sExpected) {
        std::cerr << "Check failed: not equal" << std::endl;
        ret = -1;
    }

    return ret;
}