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
    int ret = 0;

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
    if (!yaml.loadFromString("rm_elem_in_map", sTestYaml, sError)) {
        std::cerr << "Error parsing " << sError << std::endl;
        return -1;
    }

    WsjcppYamlNode *pMap1 = yaml.getRoot()->getElement("map1");
    WsjcppYamlNode *pMap11 = pMap1->getElement("map11");

    if (!pMap11->hasElement("map111")) {
        std::cerr << "Failed check 'has map111'" << std::endl;
        ret = -1;
    }

    if (!pMap11->hasElement("map112")) {
        std::cerr << "Failed check 'has map112'" << std::endl;
        ret = -1;
    }

    if (!pMap11->hasElement("map113")) {
        std::cerr << "Failed check 'has map113'" << std::endl;
        ret = -1;
    }

    pMap11->removeElement("map112");

    if (!pMap11->hasElement("map111")) {
        std::cerr << "Failed check 'has map111'" << std::endl;
        ret = -1;
    }

    if (pMap11->hasElement("map112")) {
        std::cerr << "Failed check 'has map112'" << std::endl;
        ret = -1;
    }

    if (!pMap11->hasElement("map113")) {
        std::cerr << "Failed check 'has map113'" << std::endl;
        ret = -1;
    }

    pMap11->removeElement("map111");

    if (pMap11->hasElement("map111")) {
        std::cerr << "Failed check 'has map111'" << std::endl;
        ret = -1;
    }

    if (pMap11->hasElement("map112")) {
        std::cerr << "Failed check 'has map112'" << std::endl;
        ret = -1;
    }

    if (!pMap11->hasElement("map113")) {
        std::cerr << "Failed check 'has map113'" << std::endl;
        ret = -1;
    }

    if (!pMap1->hasElement("map11")) {
        std::cerr << "Failed check 'has map11'" << std::endl;
        ret = -1;
    }

    yaml.getRoot()->getElement("map1")->removeElement("map11");

    if (pMap1->hasElement("map11")) {
        std::cerr << "Failed check 'has map11'" << std::endl;
        ret = -1;
    }

    return ret;
}