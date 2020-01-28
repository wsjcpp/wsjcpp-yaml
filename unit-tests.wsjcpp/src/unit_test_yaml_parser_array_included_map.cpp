#include "unit_test_yaml_parser_array_included_map.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_UNIT_TEST(UnitTestYamlParserArrayIncludedMap)

UnitTestYamlParserArrayIncludedMap::UnitTestYamlParserArrayIncludedMap()
    : UnitTestBase("UnitTestYamlParserArrayIncludedMap") {
    //
}

// ---------------------------------------------------------------------

void UnitTestYamlParserArrayIncludedMap::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserArrayIncludedMap::run() {

    std::string g_sTestYaml = 
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

    bool bTestSuccess = true;
    
    WSJCppYAML yaml;
    if (!yaml.loadFromString(g_sTestYaml)) {
        WSJCppLog::err(TAG, "Error parsing");
        return false;
    }
    
    WSJCppYAMLItem *pItem = nullptr;

    compareS(bTestSuccess, "param1-value", yaml.getRoot()->getElement("param1")->getValue(), "none value1");
    compareS(bTestSuccess, "param1-line", yaml.getRoot()->getElement("param1")->getPlaceInFile().getLine(), "param1: none value1 # it's value for something # olala  ");
    compareN(bTestSuccess, "param1-original-number-of-line", yaml.getRoot()->getElement("param1")->getPlaceInFile().getNumberOfLine(), 1);
    compareS(bTestSuccess, "param1-comment", yaml.getRoot()->getElement("param1")->getComment(), "it's value for something # olala");

    compareN(bTestSuccess, "array-test2-length", yaml.getRoot()->getElement("array-test2")->getLength(), 3);
    compareS(bTestSuccess, "array-test2-comment", yaml.getRoot()->getElement("array-test2")->getComment(), "some comment 2");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(0);
    compareS(bTestSuccess, "array-test2-element0-value", pItem->getValue(), "value21");
    compareS(bTestSuccess, "array-test2-element0-comment", pItem->getComment(), "comment v21");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(1);
    compareS(bTestSuccess, "array-test2-element1-value", yaml["array-test2"][1].getValue(), "value22");
    compareS(bTestSuccess, "array-test2-element1-comment", yaml["array-test2"][1].getComment(), "comment v22");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(2);
    compareS(bTestSuccess, "array-test2-element2-value", pItem->getValue(), "true");
    compareS(bTestSuccess, "array-test2-element2-comment", pItem->getComment(), "comment true");

    compareN(bTestSuccess, "array-and-map-length", yaml["array-and-map"].getLength(), 2);
    
    pItem = yaml.getRoot()->getElement("array-and-map")->getElement(0);
    compareS(bTestSuccess, "array-and-map-element0-value", pItem->getElement("submap-param1")->getValue(), "v01");
    compareS(bTestSuccess, "array-and-map-element0-value", pItem->getElement("submap-param2")->getValue(), "v02");

    pItem = yaml.getRoot()->getElement("array-and-map")->getElement(1);
    compareS(bTestSuccess, "array-and-map-element1-value", pItem->getElement("submap-param1")->getValue(), "v11");
    compareS(bTestSuccess, "array-and-map-element1-value", pItem->getElement("submap-param2")->getValue(), "v12");

    compareS(bTestSuccess, "param2-value", yaml.getRoot()->getElement("param2")->getValue(), "v2");

    std::string sSaved = "";
    if (yaml.saveToString(sSaved)) {
        compareS(bTestSuccess, "yaml_save", sSaved, 
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
            "param2: v2"
        );
    } else {
        WSJCppLog::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}