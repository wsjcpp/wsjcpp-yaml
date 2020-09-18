#include "unit_test_yaml_parser_quotes.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestYamlParserQuotes)

UnitTestYamlParserQuotes::UnitTestYamlParserQuotes()
    : WsjcppUnitTestBase("UnitTestYamlParserQuotes") {
    //
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserQuotes::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestYamlParserQuotes::executeTest() {

    std::string g_sTestYaml = 
        "# Some comment 1\n"
        "param1: \"value1\" # v1\n"
        "param2: \" #$!!!value2\" # val 2\n"
        "\" param3 olala\" : val 3 # val 3*** \n"
        "url: \"https://github.com/wsjcpp/wsjcpp-yaml\"\n"
        "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues\n"
        "empty: \"\"\n"
        "array:\n"
        "  - \"https://github.com/wsjcpp/wsjcpp-core:v0.0.1\"\n"
    ;


    
    WsjcppYaml yaml;
    if (!compare("Error parsing", yaml.loadFromString(g_sTestYaml), true)) {
        return;
    }

    // TODO: .findLine(0)

    compare("param1", yaml["param1"].getValue(), "value1");
    compare("param1", yaml["param1"].getComment(), "v1");
    
    compare("param2", yaml["param2"].getValue(), " #$!!!value2");
    compare("param2", yaml["param2"].getComment(), "val 2");

    compare(" param3 olala", yaml[" param3 olala"].getValue(), "val 3");
    compare(" param3 olala", yaml[" param3 olala"].getComment(), "val 3***");

    compare("url-value", yaml["url"].getValue(), "https://github.com/wsjcpp/wsjcpp-yaml");
    compare("issues-value", yaml["issues"].getValue(), "https://github.com/wsjcpp/wsjcpp-yaml/issues");
    compare("empty-value", yaml["empty"].getValue(), "");

    compare("array-element0-value", yaml["array"][0].getValue(), "https://github.com/wsjcpp/wsjcpp-core:v0.0.1");

    std::string sSaved = "";
    compare("save yaml", yaml.saveToString(sSaved), true);
    compare("yaml_save", sSaved,
        "# Some comment 1\n"
        "param1: \"value1\" # v1\n"
        "param2: \" #$!!!value2\" # val 2\n"
        "\" param3 olala\": val 3 # val 3***\n"
        "url: \"https://github.com/wsjcpp/wsjcpp-yaml\"\n"
        "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues\n"
        "empty: \"\"\n"
        "array:\n"
        "  - \"https://github.com/wsjcpp/wsjcpp-core:v0.0.1\""
    );    
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserQuotes::doAfterTest() {
    // nothing
    return true;
}