#include "unit_test_yaml_parser_hierarchical_map.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_UNIT_TEST(UnitTestYamlParserHierarchicalMap)

UnitTestYamlParserHierarchicalMap::UnitTestYamlParserHierarchicalMap()
    : UnitTestBase("UnitTestYamlParserHierarchicalMap") {
    //
}

// ---------------------------------------------------------------------

void UnitTestYamlParserHierarchicalMap::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserHierarchicalMap::run() {

    std::string g_sTestYaml = 
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

    bool bTestSuccess = true;
    
    WSJCppYAML yaml;
    if (!yaml.loadFromString(g_sTestYaml)) {
        WSJCppLog::err(TAG, "Error parsing");
        return false;
    }
    
    WSJCppYAMLItem *pItem = nullptr;

    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map111");
    compareS(bTestSuccess, "param1111", pItem->getElement("param1111")->getValue(), "v1111");
    compareS(bTestSuccess, "param1112", pItem->getElement("param1112")->getValue(), "v1112");
    
    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map112");
    compareS(bTestSuccess, "param1121", pItem->getElement("param1121")->getValue(), "v1121");
    compareS(bTestSuccess, "param1122", pItem->getElement("param1122")->getValue(), "v1122");
    
    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map113");
    compareS(bTestSuccess, "param1131", pItem->getElement("param1131")->getValue(), "v1131");
    compareS(bTestSuccess, "param1132", pItem->getElement("param1132")->getValue(), "v1132");

    pItem = yaml.getRoot()->getElement("map1")->getElement("map12");
    compareS(bTestSuccess, "param121", pItem->getElement("param121")->getValue(), "v121");
    compareS(bTestSuccess, "param122", pItem->getElement("param122")->getValue(), "v122");

    pItem = yaml.getRoot()->getElement("map1")->getElement("map12")->getElement("map123");
    compareS(bTestSuccess, "param1231", pItem->getElement("param1231")->getValue(), "v1231");
    compareS(bTestSuccess, "param1232", pItem->getElement("param1232")->getValue(), "v1232");

    compareS(bTestSuccess, "param2", yaml.getRoot()->getElement("param2")->getValue(), "v2");
    compareS(bTestSuccess, "param2", yaml.getRoot()->getElement("param2")->getComment(), "some comment 2");

    std::string sSaved = "";
    if (yaml.saveToString(sSaved)) {
        compareS(bTestSuccess, "yaml_save", sSaved,
            "# Some comment 1\n"
            "map1:\n"
            "  map11:\n"
            "    map111:\n"
            "      param1111: v1111\n"
            "      param1112: v1112\n"
            "    map112:\n"
            "      param1121: v1121\n"
            "      param1122: v1122\n"
            "    map113:\n"
            "      param1131: v1131\n"
            "      param1132: v1132\n"
            "  map12:\n"
            "    param121: v121\n"
            "    param122: v122\n"
            "    map123:\n"
            "      param1231: v1231\n"
            "      param1232: v1232\n"
            "param2: v2 # some comment 2"
        );
    } else {
        WSJCppLog::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}