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
        "param1: value1 # comment 2 # comment\n"
        "param2: \"111 #22\" # some \"comment 3\"\n"
        "# Some comment 4\n"
        "array1: # comment 5\n"
        "  - val1 # comment 6\n"
        "  # comment 7\n"
        "  \n"
        "  - val2 # comment 8\n"
        "map1: # comment 9\n"
        "  p1: val 1 # comment 10\n"
        "  # comment 11\n"
        "  p2: val 2 # comment 12\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("comments.yaml", sTestYaml, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    int ret = 0;
    // TODO: .findLine(0)

    // param1 via cursor

    if (yaml["param1"].valStr() != "value1") {
        std::cerr << "Element 'param1' expected 'value1'" << std::endl;
        ret = -1;
    }

    if (yaml["param1"].comment() != "comment 2 # comment") {
        std::cerr << "For element 'param1' expected comment 'comment 2 # comment'" << std::endl;
        ret = -1;
    }

    // param1 via node element

    if (yaml.getRoot()->getElement("param1")->getValue() != "value1") {
        std::cerr << "Element 'param2' expected 'value1'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param1")->getComment() != "comment 2 # comment") {
        std::cerr << "For element 'param1' expected comment 'comment 2 # comment'" << std::endl;
        ret = -1;
    }

    // param2 via cursor

    if (yaml["param2"].valStr() != "111 #22") {
        std::cerr << "Element 'param2' expected '111 #22'" << std::endl;
        ret = -1;
    }

    if (yaml["param2"].comment() != "some \"comment 3\"") {
        std::cerr << "For element 'param1' expected comment 'comment 2 # comment'" << std::endl;
        ret = -1;
    }

    // param2 via node element

    if (yaml.getRoot()->getElement("param2")->getValue() != "111 #22") {
        std::cerr << "Element 'param2' expected '111 #22'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param2")->getComment() != "some \"comment 3\"") {
        std::cerr << "For element 'param2' expected comment 'some \"comment 3\"'" << std::endl;
        ret = -1;
    }

    // commets by arrays

    if (yaml.getRoot()->getElement("array1")->getComment() != "comment 5") {
        std::cerr << "Element 'array1' expected comment 'comment 5'" << std::endl;
        ret = -1;
    }

    // array size

    if (yaml.getRoot()->getElement("array1")->getLength() != 2) {
        std::cerr << "Element 'array1' expected length equal 2" << std::endl;
        ret = -1;
    }

    // array 0-element

    if (yaml.getRoot()->getElement("array1")->getElement(0)->getValue() != "val1") {
        std::cerr << "Element 'array1' expected value of 0-element 'val1'" << std::endl;
        ret = -1;
    }

    if (yaml["array1"][0].valStr() != "val1") {
        std::cerr << "Element 'array1' expected value of 0-element 'val1' (via cursor)" << std::endl;
        ret = -1;
    }

    if (yaml["array1"][0].comment() != "comment 6") {
        std::cerr << "Element 'array1' expected comment of 0-element 'comment 6' (via cursor)" << std::endl;
        ret = -1;
    }

    // TODO: .findLine(7)

    // array 1-element

    if (yaml.getRoot()->getElement("array1")->getElement(1)->getValue() != "val2") {
        std::cerr << "Element 'array1' expected value of 1-element 'val2'" << std::endl;
        ret = -1;
    }

    if (yaml["array1"][1].valStr() != "val2") {
        std::cerr << "Element 'array1' expected value of 1-element 'val2' (via cursor)" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("array1")->getElement(1)->getComment() != "comment 8") {
        std::cerr << "Element 'array1' expected comment of 1-element 'comment 8'" << std::endl;
        ret = -1;
    }

    if (yaml["array1"][1].comment() != "comment 8") {
        std::cerr << "Element 'array1' expected comment of 1-element 'comment 8' (via cursor)" << std::endl;
        ret = -1;
    }

    // map comments

    if (yaml.getRoot()->getElement("map1")->getComment() != "comment 9") {
        std::cerr << "Element 'map1' expected comment 'comment 9'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("map1")->getElement("p1")->getComment() != "comment 10") {
        std::cerr << "Element 'map1' expected comment of p1-element 'comment 10'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("map1")->getElement("p2")->getComment() != "comment 12") {
        std::cerr << "Element 'map1' expected comment of p2-element 'comment 10'" << std::endl;
        ret = -1;
    }

    // map comments via cursor

    if (yaml["map1"].comment() != "comment 9") {
        std::cerr << "Element 'map1' expected comment 'comment 9' (via cursor)" << std::endl;
        ret = -1;
    }

    if (yaml["map1"]["p1"].comment() != "comment 10") {
        std::cerr << "Element 'map1' expected comment of p1-element 'comment 10'" << std::endl;
        ret = -1;
    }

    if (yaml["map1"]["p2"].comment() != "comment 12") {
        std::cerr << "Element 'map1' expected comment of p2-element 'comment 12'" << std::endl;
        ret = -1;
    }

    std::string saved_yaml = "";
    if (!yaml.saveToString(saved_yaml, sError)) {
        std::cerr << "Could not save yaml to string" << std::endl;
        ret = -1;
    }
    std::string expected_yaml =
        "# Some comment 1\n"
        "param1: value1 # comment 2 # comment\n"
        "param2: \"111 #22\" # some \"comment 3\"\n"
        "# Some comment 4\n"
        "array1: # comment 5\n"
        "  - val1 # comment 6\n"
        "  # comment 7\n"
        "\n"
        "  - val2 # comment 8\n"
        "map1: # comment 9\n"
        "  p1: val 1 # comment 10\n"
        "  # comment 11\n"
        "  p2: val 2 # comment 12\n"
    ;

    if (saved_yaml != expected_yaml) {
        std::cerr << "Expected '" + expected_yaml + "', but got '" << saved_yaml << "'" << std::endl;
        ret = -1;
    }


    return ret;
}