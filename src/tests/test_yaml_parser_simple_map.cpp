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
        "param1: value1\n"
        "param2: value2 # some comment 2\n"
        "\n" // empty line
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("simple_map", sTestYaml, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    WsjcppYamlNode *pItem = nullptr;
    if (yaml.getRoot()->getElement("param1")->getValue() != "value1") {
        std::cerr << "param1" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("param2")->getValue() != "value2") {
        std::cerr << "param2" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("param2")->getComment() != "some comment 2") {
        std::cerr << "param2" << std::endl;
        return -1;
    }

    std::string sSaved = "";
    bool bResult = yaml.saveToString(sSaved, sError);
    if (bResult != true) {
        std::cerr << "save yaml" << std::endl;
        return -1;
    }

    std::string sExpecetdYaml = ""
        "# Some comment 1\n"
        "param1: value1\n"
        "param2: value2 # some comment 2\n"
    ;

    if (sSaved != sExpecetdYaml) {
        std::cerr << "yaml_save not equal save and expected" << std::endl;
        return -1;
    }

    return 0;
}
