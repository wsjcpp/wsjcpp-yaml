#include "unit_test_yaml_parser_simple_array.h"
#include <vector>
#include <iostream>
#include <fallen.h>
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
    ;

    bool bTestSuccess = true;
    
    WSJCppYAML yaml;
    if (yaml.loadFromString(g_sTestYaml)) {
        Log::throw_err(TAG, "Error parsing");
        return -1;
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
            "  - 1"
        );
    } else {
        Log::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}