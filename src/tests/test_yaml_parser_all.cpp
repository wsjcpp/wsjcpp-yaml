#include <iostream>
#include <wsjcpp_yaml.h>

int main() {
    std::string sTestYaml =
        "# Some comment 1\n"
        "test10: one\n"
        "test20: two # some comment 2\n"
        "\n" // empty line
        "array30:\n"
        "  - one31 # this field for test array30\n"
        "  - two32\n"
        "  - three33\n"
        "\n" // empty line
        "array40: # some comment 3\n"
        "  - \"one#1\" # some comment\n"
        "  # some comment\n"
        "  - \"two#2\"\n"
        "array50: # some comment 3\n"
        "  - p1: test501\n"
        "    p2: test502\n"
        "  - p1: test503\n"
        "    p2: test504\n"
        "\n" // empty line
        "map60: # some comment 4\n"
        "  test70: opa1\n"
        "  test80: opa2"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("parse_all", sTestYaml, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    std::string sSaved1 = "";
    if (!yaml.saveToString(sSaved1, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    WsjcppYamlNode *pItem = nullptr;
    if (yaml.getRoot()->getElement("test10")->getValue() != "one") {
        std::cerr << "Failed check element 'test10'" << std::endl;
        return -1;
    }
    if (yaml.getRoot()->getElement("test20")->getValue() != "two") {
        std::cerr << "Failed check element 'test20'" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("array30");
    if (pItem->getLength() != 3) {
        std::cerr << "Failed check element 'array30_length'" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("array30")->getElement(0);
    if (pItem->getValue() != "one31") {
        std::cerr << "Failed check element 'test30_value'" << std::endl;
        return -1;
    }
    if (pItem->getComment() != "this field for test array30") {
        std::cerr << "Failed check element 'test30_comment'" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("array30")->getElement(1);
    if (pItem->getValue() != "two32") {
        std::cerr << "Failed check element 'test40_value'" << std::endl;
        return -1;
    }
    if (pItem->getComment() != "") {
        std::cerr << "Failed check element 'test40_comment'" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("array40");
    if (pItem->getLength() != 2) {
        std::cerr << "Failed check element 'array40_length'" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("array50");
    if (pItem->getLength() != 2) {
        std::cerr << "Failed check element 'array50_length'" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("map60")->getElement("test70");
    if (pItem->getValue() != "opa1") {
        std::cerr << "Failed check element 'test70_value'" << std::endl;
        return -1;
    }

    pItem = yaml.getRoot()->getElement("map60")->getElement("test80");
    if (pItem->getValue() != "opa2") {
        std::cerr << "Failed check element 'test80_comment'" << std::endl;
        return -1;
    }

    std::string sSaved2 = "";
    if (!yaml.saveToString(sSaved2, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }
    if (sSaved1 != sSaved2) {
        std::cerr << "Expected '" << sSaved2 << "' but got '" << sSaved1 << "'" << std::endl;
        return -1;
    }
}