#include "unit_test_yaml_parser_quotes.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_UNIT_TEST(UnitTestYamlParserQuotes)

UnitTestYamlParserQuotes::UnitTestYamlParserQuotes()
    : WsjcppUnitTestBase("UnitTestYamlParserQuotes") {
    //
}

// ---------------------------------------------------------------------

void UnitTestYamlParserQuotes::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserQuotes::run() {

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

    bool bTestSuccess = true;
    
    WsjcppYaml yaml;
    if (!yaml.loadFromString(g_sTestYaml)) {
        WsjcppLog::err(TAG, "Error parsing");
        return false;
    }

    // TODO: .findLine(0)

    compareS(bTestSuccess, "param1", yaml["param1"].getValue(), "value1");
    compareS(bTestSuccess, "param1", yaml["param1"].getComment(), "v1");
    
    compareS(bTestSuccess, "param2", yaml["param2"].getValue(), " #$!!!value2");
    compareS(bTestSuccess, "param2", yaml["param2"].getComment(), "val 2");

    compareS(bTestSuccess, " param3 olala", yaml[" param3 olala"].getValue(), "val 3");
    compareS(bTestSuccess, " param3 olala", yaml[" param3 olala"].getComment(), "val 3***");

    compareS(bTestSuccess, "url-value", yaml["url"].getValue(), "https://github.com/wsjcpp/wsjcpp-yaml");
    compareS(bTestSuccess, "issues-value", yaml["issues"].getValue(), "https://github.com/wsjcpp/wsjcpp-yaml/issues");
    compareS(bTestSuccess, "empty-value", yaml["empty"].getValue(), "");

    compareS(bTestSuccess, "array-element0-value", yaml["array"][0].getValue(), "https://github.com/wsjcpp/wsjcpp-core:v0.0.1");

    std::string sSaved = "";
    if (yaml.saveToString(sSaved)) {
        compareS(bTestSuccess, "yaml_save", sSaved,
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
    } else {
        WsjcppLog::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}