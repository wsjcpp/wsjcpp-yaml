#include "unit_test_yaml_parser_simple_array.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_UNIT_TEST(UnitTestYamlParserSimpleArray)

UnitTestYamlParserSimpleArray::UnitTestYamlParserSimpleArray()
    : UnitTestBase("UnitTestYamlParserSimpleArray") {
    //
}

// ---------------------------------------------------------------------

void UnitTestYamlParserSimpleArray::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserSimpleArray::run() {

    std::string g_sTestYaml = 
        "# simple array test\n"
        "param1: none value1 # it's value for something # olala  \n"
        "array-test2 : #    some comment 2   \n"
        "  - value21 # comment v21 \n"
        "  - value22 # comment v22 \n"
        "  - true # comment true \n"
        "  # some\n"
        "  - falsesome   \n"
        "  - free@free   \n"
        "  - # empty \n"
        "  - 1\n"
        "param2: val2 #  value 2 \n"
    ;

    bool bTestSuccess = true;
    
    WSJCppYAML yaml;
    if (!yaml.loadFromString(g_sTestYaml)) {
        WSJCppLog::err(TAG, "Error parsing");
        return false;
    }
    
    WSJCppYAMLItem *pItem = nullptr;

    compareS(bTestSuccess, "param1-value", yaml.getRoot()->getElement("param1")->getValue(), "none value1");
    compareS(bTestSuccess, "param1-line", yaml.getRoot()->getElement("param1")->getOriginalLine(), "param1: none value1 # it's value for something # olala  ");
    compareN(bTestSuccess, "param1-original-number-of-line", yaml.getRoot()->getElement("param1")->getOriginalNumberOfLine(), 1);
    compareS(bTestSuccess, "param1-comment", yaml.getRoot()->getElement("param1")->getComment(), "it's value for something # olala");

    compareN(bTestSuccess, "array-test2-length", yaml.getRoot()->getElement("array-test2")->getLength(), 7);
    compareS(bTestSuccess, "array-test2-comment", yaml.getRoot()->getElement("array-test2")->getComment(), "some comment 2");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(0);
    compareS(bTestSuccess, "array-test2-element0-value", pItem->getValue(), "value21");
    compareS(bTestSuccess, "array-test2-element0-comment", pItem->getComment(), "comment v21");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(1);
    compareS(bTestSuccess, "array-test2-element1-value", pItem->getValue(), "value22");
    compareS(bTestSuccess, "array-test2-element1-comment", pItem->getComment(), "comment v22");

    compareS(bTestSuccess, "array-test2-element2-value", yaml["array-test2"][2].getValue(), "true");
    compareS(bTestSuccess, "array-test2-element2-line", yaml["array-test2"][2].getOriginalLine(), "  - true # comment true ");
    compareN(bTestSuccess, "array-test2-element2-original-number-of-line", yaml["array-test2"][2].getOriginalNumberOfLine(), 5);
    compareS(bTestSuccess, "array-test2-element2-comment", yaml["array-test2"][2].getComment(), "comment true");

    compareS(bTestSuccess, "array-test2-element3-value", yaml["array-test2"][3].getValue(), "falsesome");
    compareS(bTestSuccess, "array-test2-element3-line", yaml["array-test2"][3].getOriginalLine(), "  - falsesome   ");
    compareN(bTestSuccess, "array-test2-element3-original-number-of-line", yaml["array-test2"][3].getOriginalNumberOfLine(), 7);
    compareS(bTestSuccess, "array-test2-element3-comment", yaml["array-test2"][3].getComment(), "");
    
    compareS(bTestSuccess, "array-test2-element4-value", yaml["array-test2"][4].getValue(), "free@free");
    compareS(bTestSuccess, "array-test2-element4-line", yaml["array-test2"][4].getOriginalLine(), "  - free@free   ");
    compareN(bTestSuccess, "array-test2-element4-original-number-of-line", yaml["array-test2"][4].getOriginalNumberOfLine(), 8);
    compareS(bTestSuccess, "array-test2-element4-comment", yaml["array-test2"][4].getComment(), "");

    compareS(bTestSuccess, "array-test2-element5-value", yaml["array-test2"][5].getValue(), "");
    compareS(bTestSuccess, "array-test2-element5-line", yaml["array-test2"][5].getOriginalLine(), "  - # empty ");
    compareN(bTestSuccess, "array-test2-element5-original-number-of-line", yaml["array-test2"][5].getOriginalNumberOfLine(), 9);
    compareS(bTestSuccess, "array-test2-element5-comment", yaml["array-test2"][5].getComment(), "empty");

    compareS(bTestSuccess, "array-test2-element6-value", yaml["array-test2"][6].getValue(), "1");
    compareS(bTestSuccess, "array-test2-element6-line", yaml["array-test2"][6].getOriginalLine(), "  - 1");
    compareN(bTestSuccess, "array-test2-element6-original-number-of-line", yaml["array-test2"][6].getOriginalNumberOfLine(), 10);
    compareS(bTestSuccess, "array-test2-element6-comment", yaml["array-test2"][6].getComment(), "");

    compareS(bTestSuccess, "param2-value", yaml.getRoot()->getElement("param2")->getValue(), "val2");
    compareS(bTestSuccess, "param2-line", yaml.getRoot()->getElement("param2")->getOriginalLine(), "param2: val2 #  value 2 ");
    compareN(bTestSuccess, "param2-original-number-of-line", yaml.getRoot()->getElement("param2")->getOriginalNumberOfLine(), 11);
    compareS(bTestSuccess, "param2-comment", yaml.getRoot()->getElement("param2")->getComment(), "value 2");

    std::string sSaved = "";
    if (yaml.saveToString(sSaved)) {
        compareS(bTestSuccess, "yaml_save", sSaved, 
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
            "param2: val2 # value 2"
        );
    } else {
        WSJCppLog::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}