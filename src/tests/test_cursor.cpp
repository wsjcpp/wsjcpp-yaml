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

#include <wsjcpp_yaml.h>

int main() {

     std::string sTestYaml =
        "# Some comment 1\n"
        "map1: \n"
        "  map11: \n"
        "    sss: \n"
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
        "    param1232: v1232\n"
        "param2: v2 # some comment 2\n"
        "arr1: # some comment array 1\n"
        "  - some1\n"
        "  - 3\n"
        "\n"
        "  - Yes\n"
        "  # empty\n"
        "  - no\n"
        "  - true\n"
        "  - False\n"
        "\n" // empty line
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("test_cursor", sTestYaml, sError)) {
        std::cerr << "Error parsing " << sError << std::endl;
        return -1;
    }

    if (yaml["map1"].isNull() != false) {
        std::cerr << "map1 is null" << std::endl;
        return -1;
    }
    if (yaml["map1"].isUndefined() != false) {
        std::cerr << "map1 is undefined" << std::endl;
        return -1;
    }
    if (yaml["map1"].isValue() != false) {
        std::cerr << "map1 is value" << std::endl;
        return -1;
    }
    if (yaml["map1"].isArray() != false) {
        std::cerr << "map1 is array" << std::endl;
        return -1;
    }
    if (yaml["map1"].isMap() != true) {
        std::cerr << "map1 is map" << std::endl;
        return -1;
    }

    if (yaml["map1-1111"].isNull() != true) {
        std::cerr << "map1-1111 is null" << std::endl;
        return -1;
    }
    if (yaml["map1-1111"].isUndefined() != false) {
        std::cerr << "map1 is undefined" << std::endl;
        return -1;
    }
    if (yaml["map1-1111"].isValue() != false) {
        std::cerr << "map1 is value" << std::endl;
        return -1;
    }
    if (yaml["map1-1111"].isArray() != false) {
        std::cerr << "map1-1111 is array" << std::endl;
        return -1;
    }
    if (yaml["map1-1111"].isMap() != false) {
        std::cerr << "map1-1111 is map" << std::endl;
        return -1;
    }

    if (yaml["arr1"].isNull() != false) {
        std::cerr << "arr1 is null" << std::endl;
        return -1;
    }
    if (yaml["arr1"].isUndefined() != false) {
        std::cerr << "arr1 is undefined" << std::endl;
        return -1;
    }
    if (yaml["arr1"].isValue() != false) {
        std::cerr << "arr1 is value" << std::endl;
        return -1;
    }
    if (yaml["arr1"].isArray() != true) {
        std::cerr << "arr1 is array" << std::endl;
        return -1;
    }
    if (yaml["arr1"].isMap() != false) {
        std::cerr << "arr1 is map" << std::endl;
        return -1;
    }

    if (yaml["map1"]["map11"]["sss"].isNull() != false) {
        std::cerr << "map1.map11.sss is null" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map11"]["sss"].isUndefined() != true) {
        std::cerr << "map1.map11.sss is undefined" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map11"]["sss"].isValue() != false) {
        std::cerr << "map1.map11.sss is value" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map11"]["sss"].isArray() != false) {
        std::cerr << "map1.map11.sss is array" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map11"]["sss"].isMap() != false) {
        std::cerr << "map1.map11.sss is map" << std::endl;
        return -1;
    }

    if (yaml["map1"]["map11"]["map111"]["param1111"].isNull() != false) {
        std::cerr << "map1.map11.map111.param1111 is null" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map11"]["map111"]["param1111"].isUndefined() != false) {
        std::cerr << "map1.map11.map111.param1111 is undefined" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map11"]["map111"]["param1111"].isValue() != true) {
        std::cerr << "map1.map11.map111.param1111 is value" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map11"]["map111"]["param1111"].isArray() != false) {
        std::cerr << "map1.map11.map111.param1111 is array" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map11"]["map111"]["param1111"].isMap() != false) {
        std::cerr << "map1.map11.map111.param1111 is map" << std::endl;
        return -1;
    }

    if (yaml["map1"][0].isNull() != true) {
        std::cerr << "map use as array" << std::endl;
        return -1;
    }
    if (yaml["arr1"]["0"].isNull() != true) {
        std::cerr << "array use as map" << std::endl;
        return -1;
    }
    if (yaml["arr1"][0].isNull() != false) {
        std::cerr << "array use as array" << std::endl;
        return -1;
    }

    if (yaml["arr1"].comment() != "some comment array 1") {
        std::cerr << "array 1 comment" << std::endl;
        return -1;
    }
    if (yaml["arr1"].size() != 6) {
        std::cerr << "array size 6" << std::endl;
        return -1;
    }
    if (yaml["arr1"][0].valStr() != "some1") {
        std::cerr << "array el 0" << std::endl;
        return -1;
    }
    if (yaml["arr1"][1].valStr() != "3") {
        std::cerr << "array el 1" << std::endl;
        return -1;
    }
    if (yaml["arr1"][2].valStr() != "Yes") {
        std::cerr << "array el 2" << std::endl;
        return -1;
    }
    if (yaml["arr1"][3].valStr() != "no") {
        std::cerr << "array el 3" << std::endl;
        return -1;
    }
    if (yaml["arr1"][4].valStr() != "true") {
        std::cerr << "array el 4" << std::endl;
        return -1;
    }
    if (yaml["arr1"][5].valStr() != "False") {
        std::cerr << "array el 5" << std::endl;
        return -1;
    }

    if (yaml["arr1"][2].valBool() != true) {
        std::cerr << "array bool el 2" << std::endl;
        return -1;
    }
    if (yaml["arr1"][3].valBool() != false) {
        std::cerr << "array bool el 3" << std::endl;
        return -1;
    }
    if (yaml["arr1"][4].valBool() != true) {
        std::cerr << "array bool el 4" << std::endl;
        return -1;
    }
    if (yaml["arr1"][5].valBool() != false) {
        std::cerr << "array bool el 5" << std::endl;
        return -1;
    }

    // int
    if (yaml["arr1"][1].valInt() != 3) {
        std::cerr << "array 1 val 3" << std::endl;
        return -1;
    }
    yaml["arr1"][1].val(10);
    if (yaml["arr1"][1].valInt() != 10) {
        std::cerr << "array 1 val 10" << std::endl;
        return -1;
    }

    // string
    if (yaml["arr1"][0].valStr() != "some1") {
        std::cerr << "array el 0 - 1" << std::endl;
        return -1;
    }

    yaml["arr1"][0].val("different value").comment("1234");
    if (yaml["arr1"][0].valStr() != "different value") {
        std::cerr << "array el 0 - 2" << std::endl;
        return -1;
    }
    if (yaml["arr1"][0].comment() != "1234") {
        std::cerr << "array el 0 - 3" << std::endl;
        return -1;
    }

    // bool
    if (yaml["arr1"][4].valStr() != "true") {
        std::cerr << "array bool el 4 (1)" << std::endl;
        return -1;
    }
    if (yaml["arr1"][4].node()->getValue() != "true") {
        std::cerr << "array bool el 4 (2)" << std::endl;
        return -1;
    }
    if (yaml["arr1"][4].valBool() != true) {
        std::cerr << "array bool el 4 (3)" << std::endl;
        return -1;
    }
    yaml["arr1"][4].val(true);
    if (yaml["arr1"][4].valStr() != "yes") {
        std::cerr << "array bool el 4 (4)" << std::endl;
        return -1;
    }
    if (yaml["arr1"][4].valBool() != true) {
        std::cerr << "array bool el 4 (5)" << std::endl;
        return -1;
    }
    yaml["arr1"][4].val(false);
    if (yaml["arr1"][4].valStr() != "no") {
        std::cerr << "array bool el 4 (6)" << std::endl;
        return -1;
    }
    if (yaml["arr1"][4].valBool() != false) {
        std::cerr << "array bool el 4 (7)" << std::endl;
        return -1;
    }

    // map
    if (yaml["map1"]["map12"].isMap() != true) {
        std::cerr << "map1.map12" << std::endl;
        return -1;
    }

    std::vector<std::string> vKeys = yaml["map1"]["map12"].keys();
    if (vKeys.size() != 4) {
        std::cerr << "map1.map12 keys size" << std::endl;
        return -1;
    }
    if (vKeys.size() == 4) {
        if (vKeys[0] != "param121") {
            std::cerr << "map1.map12 keys 0" << std::endl;
            return -1;
        }
        if (vKeys[1] != "param122") {
            std::cerr << "map1.map12 keys 1" << std::endl;
            return -1;
        }
        if (vKeys[2] != "map123") {
            std::cerr << "map1.map12 keys 2" << std::endl;
            return -1;
        }
        if (vKeys[3] != "param1232") {
            std::cerr << "map1.map12 keys 3" << std::endl;
            return -1;
        }
    }
    if (yaml["map1"]["map12"].hasKey("some") != false) {
        std::cerr << "map1.map12 has key1" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map12"].hasKey("map123") != true) {
        std::cerr << "map1.map12 has key2" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map12"]["map123"].isValue() != false) {
        std::cerr << "map1.map12 is value" << std::endl;
        return -1;
    }
    if (yaml["map1"]["map12"]["param122"].isValue() != true) {
        std::cerr << "map1.map12 is value" << std::endl;
        return -1;
    }


    /*    WsjcppYamlCursor &push(const std::string &sVal);
        WsjcppYamlCursor &push(int nVal);
        WsjcppYamlCursor &push(bool bVal);
        WsjcppYamlCursor &remove(int nIdx);*/

    return 0;
}
