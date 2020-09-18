#include "unit_test_yaml_parser_simple_map.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestYamlParserSimpleMap)

UnitTestYamlParserSimpleMap::UnitTestYamlParserSimpleMap()
    : WsjcppUnitTestBase("UnitTestYamlParserSimpleMap") {
    //
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserSimpleMap::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestYamlParserSimpleMap::executeTest() {

    std::string g_sTestYaml = 
        "# Some comment 1\n"
        "param1: value1\n"
        "param2: value2 # some comment 2\n"
        "\n" // empty line
    ;
    
    WsjcppYaml yaml;
     if (!compare("Error parsing", yaml.loadFromString(g_sTestYaml), true)) {
        return;
    }
    
    WsjcppYamlItem *pItem = nullptr;
    compare("param1", yaml.getRoot()->getElement("param1")->getValue(), "value1");
    compare("param2", yaml.getRoot()->getElement("param2")->getValue(), "value2");
    compare("param2", yaml.getRoot()->getElement("param2")->getComment(), "some comment 2");

    std::string sSaved = "";
    bool bResult = yaml.saveToString(sSaved);
    if (compare("save yaml", bResult, true)) {
        compare("yaml_save", sSaved,
            "# Some comment 1\n"
            "param1: value1\n"
            "param2: value2 # some comment 2"
        );
    }
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserSimpleMap::doAfterTest() {
    // nothing
    return true;
}