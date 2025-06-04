#include <iostream>
#include <wsjcpp_yaml.h>

int main() {

    std::string sTestYaml =
        "#test array included map\n"
        "param1: none value1 # it's value for something # olala  \n"
        "array-test2 : #    some comment 2   \n"
        "  - value21 # comment v21 \n"
        "  - value22 # comment v22 \n"
        "  - true # comment true \n"
        "  # some\n"
        "array-and-map:\n"
        "  - submap-param1: v01\n"
        "    submap-param2: v02\n"
        "  - submap-param1: v11\n"
        "    submap-param2: v12\n"
        "param2: v2\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("map_in_array", sTestYaml, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    WsjcppYamlNode *pItem = nullptr;

    int ret = 0;
    if (yaml.getRoot()->getElement("param1")->getValue() != "none value1") {
        std::cerr << "Failed check 'param1-value' " << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param1")->getPlaceInFile().getLine() != "param1: none value1 # it's value for something # olala  ") {
        std::cerr << "Failed check 'param1-line' " << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param1")->getPlaceInFile().getNumberOfLine() != 1) {
        std::cerr << "Failed check 'param1-original-number-of-line' " << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param1")->getComment() != "it's value for something # olala") {
        std::cerr << "Failed check 'param1-original-number-of-line' " << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getLength() != 3) {
        std::cerr << "Failed check 'array-test2-length' " << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getComment() != "some comment 2") {
        std::cerr << "Failed check 'array-test2-comment' " << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(0);

    if (pItem->getValue() != "value21") {
        std::cerr << "Failed check 'array-test2-element0-value' " << std::endl;
        ret = -1;
    }

    if (pItem->getComment() != "comment v21") {
        std::cerr << "Failed check 'array-test2-element0-comment' " << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(1);

    if (yaml.getRoot()->getElement("array-test2")->getElement(1)->getValue() != "value22") {
        std::cerr << "Failed check 'array-test2-element1-value' " << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("array-test2")->getElement(1)->getComment() != "comment v22") {
        std::cerr << "Failed check 'array-test2-element1-comment' " << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(2);

    if (pItem->getValue() != "true") {
        std::cerr << "Failed check 'array-test2-element2-value' " << std::endl;
        ret = -1;
    }

    if (pItem->getComment() != "comment true") {
        std::cerr << "Failed check 'array-test2-element2-comment' " << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("array-and-map")->getLength() != 2) {
        std::cerr << "Failed check 'array-and-map-length' " << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("array-and-map")->getElement(0);

    if (pItem->getElement("submap-param1")->getValue() != "v01") {
        std::cerr << "Failed check 'array-and-map-element0-value' " << std::endl;
        ret = -1;
    }

    if (pItem->getElement("submap-param2")->getValue() != "v02") {
        std::cerr << "Failed check 'array-and-map-element0-value' " << std::endl;
        ret = -1;
    }

    pItem = yaml.getRoot()->getElement("array-and-map")->getElement(1);

    if (pItem->getElement("submap-param1")->getValue() != "v11") {
        std::cerr << "Failed check 'array-and-map-element1-value' " << std::endl;
        ret = -1;
    }

    if (pItem->getElement("submap-param2")->getValue() != "v12") {
        std::cerr << "Failed check 'array-and-map-element1-value' " << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->getElement("param2")->getValue() != "v2") {
        std::cerr << "Failed check 'param2-value' " << std::endl;
        ret = -1;
    }

    std::string sSaved = "";
    if (!yaml.saveToString(sSaved, sError)) {
        std::cerr << "Failed check 'saveToString' " << std::endl;
        ret = -1;
    } else {
        std::string sExpected =
            "# test array included map\n" // expected
            "param1: none value1 # it's value for something # olala\n"
            "array-test2: # some comment 2\n"
            "  - value21 # comment v21\n"
            "  - value22 # comment v22\n"
            "  - true # comment true\n"
            "  # some\n"
            "array-and-map:\n"
            "  - submap-param1: v01\n"
            "    submap-param2: v02\n"
            "  - submap-param1: v11\n"
            "    submap-param2: v12\n"
            "param2: v2\n"
        ;
        if (sSaved != sExpected) {
            std::cerr << "Expected '" << sExpected << "', but got '" << sSaved << "'" << std::endl;
            ret = -1;
        }
    }
    return ret;
}