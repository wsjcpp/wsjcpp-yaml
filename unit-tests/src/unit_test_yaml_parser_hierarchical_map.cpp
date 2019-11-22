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
        "param1: value1\n"
        "param2: value2 # some comment 2\n"
        "\n" // empty line
    ;

    bool bTestSuccess = true;
    
    WSJCppYAML yaml;
    if (yaml.loadFromString(g_sTestYaml)) {
        WSJCppLog::throw_err(TAG, "Error parsing");
        return -1;
    }
    
    WSJCppYAMLItem *pItem = nullptr;
    compareS(bTestSuccess, "param1", yaml.getRoot()->getElement("param1")->getValue(), "value1");
    compareS(bTestSuccess, "param2", yaml.getRoot()->getElement("param2")->getValue(), "value2");
    compareS(bTestSuccess, "param2", yaml.getRoot()->getElement("param2")->getComment(), "some comment 2");

    std::string sSaved = "";
    if (yaml.saveToString(sSaved)) {
        compareS(bTestSuccess, "yaml_save", sSaved,
            "# Some comment 1\n"
            "param1: value1\n"
            "param2: value2 # some comment 2"
        );
    } else {
        WSJCppLog::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}