#include "unit_test_yaml_parser_array_included_map.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestYamlParserArrayIncludedMap)

UnitTestYamlParserArrayIncludedMap::UnitTestYamlParserArrayIncludedMap()
    : WsjcppUnitTestBase("UnitTestYamlParserArrayIncludedMap") {
    //
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserArrayIncludedMap::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestYamlParserArrayIncludedMap::executeTest() {

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
    
    WsjcppYaml yaml;
     if (!compare("Error parsing", yaml.loadFromString(g_sTestYaml), true)) {
        return;
    }
    
    WsjcppYamlItem *pItem = nullptr;

    compare("param1-value", yaml.getRoot()->getElement("param1")->getValue(), "none value1");
    compare("param1-line", yaml.getRoot()->getElement("param1")->getPlaceInFile().getLine(), "param1: none value1 # it's value for something # olala  ");
    compare("param1-original-number-of-line", yaml.getRoot()->getElement("param1")->getPlaceInFile().getNumberOfLine(), 1);
    compare("param1-comment", yaml.getRoot()->getElement("param1")->getComment(), "it's value for something # olala");

    compare("array-test2-length", yaml.getRoot()->getElement("array-test2")->getLength(), 3);
    compare("array-test2-comment", yaml.getRoot()->getElement("array-test2")->getComment(), "some comment 2");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(0);
    compare("array-test2-element0-value", pItem->getValue(), "value21");
    compare("array-test2-element0-comment", pItem->getComment(), "comment v21");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(1);
    compare("array-test2-element1-value", yaml["array-test2"][1].getValue(), "value22");
    compare("array-test2-element1-comment", yaml["array-test2"][1].getComment(), "comment v22");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(2);
    compare("array-test2-element2-value", pItem->getValue(), "true");
    compare("array-test2-element2-comment", pItem->getComment(), "comment true");

    compare("array-and-map-length", yaml["array-and-map"].getLength(), 2);
    
    pItem = yaml.getRoot()->getElement("array-and-map")->getElement(0);
    compare("array-and-map-element0-value", pItem->getElement("submap-param1")->getValue(), "v01");
    compare("array-and-map-element0-value", pItem->getElement("submap-param2")->getValue(), "v02");

    pItem = yaml.getRoot()->getElement("array-and-map")->getElement(1);
    compare("array-and-map-element1-value", pItem->getElement("submap-param1")->getValue(), "v11");
    compare("array-and-map-element1-value", pItem->getElement("submap-param2")->getValue(), "v12");

    compare("param2-value", yaml.getRoot()->getElement("param2")->getValue(), "v2");

    std::string sSaved = "";
    if (compare("save yaml", yaml.saveToString(sSaved), true)) {
        compare("yaml_save", sSaved, 
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
    }
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserArrayIncludedMap::doAfterTest() {
    // nothing
    return true;
}