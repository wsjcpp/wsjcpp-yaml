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
#include "helpers.h"

int main() {

    std::string sFilepath = find_test_data_file("data/parser-simple-array.yml");
    WsjcppYaml yaml;
    std::string sError;

    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Parsing error " << std::endl;
        return -1;
    }

    WsjcppYamlNode *pItem = nullptr;

    if (yaml.getRoot()->getElement("param1")->getValue() != "none value1") {
        std::cerr << "param1-value" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("param1")->getPlaceInFile().getLine() != "param1: none value1 # it's value for something # olala  ") {
        std::cerr << "param1-line" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->getElement("param1")->getPlaceInFile().getNumberOfLine() != 1) {
        std::cerr << "param1-original-number-of-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("param1")->getComment() != "it's value for something # olala") {
        std::cerr << "param1-comment" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getLength() != 7) {
        std::cerr << "array-test2-length" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getComment() != "some comment 2") {
        std::cerr << "array-test2-comment" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(0);
    if (pItem->getValue() != "value21") {
        std::cerr << "array-test2-element0-value" << std::endl;
        return -1;
    }
    if (pItem->getComment() != "comment v21") {
        std::cerr << "array-test2-element0-comment" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(1);
    if (pItem->getValue() != "value22") {
        std::cerr << "array-test2-element1-value" << std::endl;
        return -1;
    }
    if (pItem->getComment() != "comment v22") {
        std::cerr << "array-test2-element1-comment" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getElement(2)->getValue() != "true") {
        std::cerr << "array-test2-element2-value" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(2)->getPlaceInFile().getLine() != "  - true # comment true ") {
        std::cerr << "array-test2-element2-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(2)->getPlaceInFile().getNumberOfLine() != 5) {
        std::cerr << "array-test2-element2-original-number-of-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(2)->getComment() != "comment true") {
        std::cerr << "array-test2-element2-comment" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getElement(3)->getValue() != "falsesome") {
        std::cerr << "array-test2-element3-value" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(3)->getPlaceInFile().getLine() != "  - falsesome   ") {
        std::cerr << "array-test2-element3-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(3)->getPlaceInFile().getNumberOfLine() != 7) {
        std::cerr << "array-test2-element3-original-number-of-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(3)->getComment() != "") {
        std::cerr << "array-test2-element3-comment" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getElement(4)->getValue() != "free@free") {
        std::cerr << "array-test2-element4-value" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(4)->getPlaceInFile().getLine() != "  - free@free   ") {
        std::cerr << "array-test2-element4-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(4)->getPlaceInFile().getNumberOfLine() != 8) {
        std::cerr << "array-test2-element4-original-number-of-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(4)->getComment() != "") {
        std::cerr << "array-test2-element4-comment" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getElement(5)->getValue() != "") {
        std::cerr << "array-test2-element5-value" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(5)->getPlaceInFile().getLine() != "  - # empty ") {
        std::cerr << "array-test2-element5-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(5)->getPlaceInFile().getNumberOfLine() != 9) {
        std::cerr << "array-test2-element5-original-number-of-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(5)->getComment() != "empty") {
        std::cerr << "array-test2-element5-comment" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getElement(6)->getValue() != "1") {
        std::cerr << "array-test2-element6-value" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(6)->getPlaceInFile().getLine() != "  - 1") {
        std::cerr << "array-test2-element6-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(6)->getPlaceInFile().getNumberOfLine() != 10) {
        std::cerr << "array-test2-element6-original-number-of-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("array-test2")->getElement(6)->getComment() != "") {
        std::cerr << "array-test2-element6-comment" << std::endl;
        return -1;
    }

    if (yaml.getRoot()->getElement("param2")->getValue() != "val2") {
        std::cerr << "param2-value" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("param2")->getPlaceInFile().getLine() != "param2: val2 #  value 2 ") {
        std::cerr << "param2-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("param2")->getPlaceInFile().getNumberOfLine() != 11) {
        std::cerr << "param2-original-number-of-line" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("param2")->getComment() != "value 2") {
        std::cerr << "param2-comment" << std::endl;
        return -1;
    }

    std::string sSaved = "";
    if (!yaml.saveToString(sSaved, sError)) {
        std::cerr << "save yaml" << std::endl;
        return -1;
    }

    std::string sExpected = ""
      "# simple array test\n" // expected
      "param1: none value1 # it's value for something # olala\n"
      "array-test2: # some comment 2\n"
      "  - value21 # comment v21\n"
      "  - value22 # comment v22\n"
      "  - true # comment true\n"
      "  # some\n"
      "  - falsesome\n"
      "  - free@free\n"
      "  - # empty\n"
      "  - 1\n"
      "param2: val2 # value 2\n"
    ;

    if (sSaved != sExpected) {
        std::cerr << "yaml_save unexpected" << std::endl;
        return -1;
    }
    return 0;
}
