#include "unit_test_yaml_parser_simple_map.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_UNIT_TEST(UnitTestYamlParserSimpleMap)

UnitTestYamlParserSimpleMap::UnitTestYamlParserSimpleMap()
    : WsjcppUnitTestBase("UnitTestYamlParserSimpleMap") {
    //
}

// ---------------------------------------------------------------------

void UnitTestYamlParserSimpleMap::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserSimpleMap::run() {

    std::string g_sTestYaml = 
        "# Some comment 1\n"
        "param1: value1\n"
        "param2: value2 # some comment 2\n"
        "\n" // empty line
    ;

    bool bTestSuccess = true;
    
    WsjcppYaml yaml;
    if (!yaml.loadFromString(g_sTestYaml)) {
        WsjcppLog::err(TAG, "Error parsing");
        return false;
    }
    
    WsjcppYamlItem *pItem = nullptr;
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
        WsjcppLog::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}