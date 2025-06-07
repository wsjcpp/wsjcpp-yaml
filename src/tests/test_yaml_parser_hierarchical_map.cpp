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
        "map1: \n"
        "  map11: \n"
        "    map111: \n"
        "      param1111: v1111\n"
        "      param1112: v1112\n"
        "    map112: \n"
        "      param1121: v1121\n"
        "      param1122: v1122\n"
        "    map113: \n"
        "      param1131: v1131\n"
        "      param1132: v1132\n"
        "  map12: \n"
        "    param121: v121\n"
        "    param122: v122\n"
        "    map123: \n"
        "      param1231: v1231\n"
        "      param1232: v1232\n"
        "param2: v2 # some comment 2\n"
        "\n" // empty line
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("hard_map", sTestYaml, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;

    WsjcppYamlNode *pItem = nullptr;

    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map111");

    if (pItem->getElement("param1111")->getValue() != "v1111") {
        std::cerr << "Check failed: param1111" << std::endl;
        ret = -1;
    }

    if (pItem->getElement("param1112")->getValue() != "v1112") {
        std::cerr << "Check failed: param1112" << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map112");

    if (pItem->getElement("param1121")->getValue() != "v1121") {
        std::cerr << "Check failed: param1121" << std::endl;
        ret = -1;
    }

    if (pItem->getElement("param1122")->getValue() != "v1122") {
        std::cerr << "Check failed: param1122" << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map113");

    if (pItem->getElement("param1131")->getValue() != "v1131") {
        std::cerr << "Check failed: param1131" << std::endl;
        ret = -1;
    }

    if (pItem->getElement("param1132")->getValue() != "v1132") {
        std::cerr << "Check failed: param1132" << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("map1")->getElement("map12");

    if (pItem->getElement("param121")->getValue() != "v121") {
        std::cerr << "Check failed: param121" << std::endl;
        ret = -1;
    }

    if (pItem->getElement("param122")->getValue() != "v122") {
        std::cerr << "Check failed: param122" << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("map1")->getElement("map12")->getElement("map123");

    if (pItem->getElement("param1231")->getValue() != "v1231") {
        std::cerr << "Check failed: param1231" << std::endl;
        ret = -1;
    }

    if (pItem->getElement("param1232")->getValue() != "v1232") {
        std::cerr << "Check failed: param1232" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param2")->getValue() != "v2") {
        std::cerr << "Check failed: param2" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param2")->getComment() != "some comment 2") {
        std::cerr << "Check failed: param2-comment" << std::endl;
        ret = -1;
    }

    std::string sSaved = "";
    if (!yaml.saveToString(sSaved, sError)) {
        std::cerr << "Error save: " << sError << std::endl;
        return -1;
    }

    std::string sExpectedYaml =
        "# Some comment 1\n"
        "map1:\n"
        "  map11:\n"
        "    map111:\n"
        "      param1111: v1111\n"
        "      param1112: v1112\n"
        "    map112:\n"
        "      param1121: v1121\n"
        "      param1122: v1122\n"
        "    map113:\n"
        "      param1131: v1131\n"
        "      param1132: v1132\n"
        "  map12:\n"
        "    param121: v121\n"
        "    param122: v122\n"
        "    map123:\n"
        "      param1231: v1231\n"
        "      param1232: v1232\n"
        "param2: v2 # some comment 2\n"
    ;

    if (sSaved != sExpectedYaml) {
        std::cerr << " sSaved != sExpectedYaml " << std::endl;
        return -1;
    }
    return ret;
}