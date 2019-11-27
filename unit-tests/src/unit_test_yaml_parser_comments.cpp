#include "unit_test_yaml_parser_comments.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_UNIT_TEST(UnitTestYamlParserComments)

UnitTestYamlParserComments::UnitTestYamlParserComments()
    : UnitTestBase("UnitTestYamlParserComments") {
    //
}

// ---------------------------------------------------------------------

void UnitTestYamlParserComments::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserComments::run() {

    std::string g_sTestYaml = 
        "# Some comment 1\n"
        "param1: value1 # comment 2 # comment\n"
        "param2: value2 # some \"comment 3\"\n"
        "# Some comment 4\n"
        "array1: # comment 5\n"
        "  - val1 # comment 6\n"
        "  # comment 7\n"
        "  \n"
        "  - val2 # comment 8\n"
        "map1: # comment 9\n"
        "  p1: val 1 # comment 10\n"
        "  # comment 11\n"
        "  p2: val 2 # comment 12\n"
    ;

    bool bTestSuccess = true;
    
    WSJCppYAML yaml;
    if (!yaml.loadFromString(g_sTestYaml)) {
        WSJCppLog::err(TAG, "Error parsing");
        return false;
    }

    // TODO: .findLine(0)

    compareS(bTestSuccess, "param1", yaml["param1"].getValue(), "value1");
    compareS(bTestSuccess, "param1", yaml["param1"].getComment(), "comment 2 # comment");
    
    compareS(bTestSuccess, "param2", yaml["param2"].getValue(), "value2");
    compareS(bTestSuccess, "param2", yaml["param2"].getComment(), "some \"comment 3\"");


    compareS(bTestSuccess, "array1-comment", yaml["array1"].getComment(), "comment 5");
    compareN(bTestSuccess, "array1-length", yaml["array1"].getLength(), 2);
    compareS(bTestSuccess, "array1-element0-value", yaml["array1"][0].getValue(), "val1");
    compareS(bTestSuccess, "array1-element0-comment", yaml["array1"][0].getComment(), "comment 6");

    // TODO: .findLine(7)

    compareS(bTestSuccess, "array1-element1-value", yaml["array1"][1].getValue(), "val2");
    compareS(bTestSuccess, "array1-element1-comment", yaml["array1"][1].getComment(), "comment 8");

    compareS(bTestSuccess, "map1-comment", yaml["map1"].getComment(), "comment 9");
    compareS(bTestSuccess, "map1-p1-comment", yaml["map1"]["p1"].getComment(), "comment 10");
    compareS(bTestSuccess, "map1-p2-comment", yaml["map1"]["p2"].getComment(), "comment 12");

    
    // compareS(bTestSuccess, "param2", yaml.getRoot()->getElement("param2")->getValue(), "value2");
    // compareS(bTestSuccess, "param2", yaml.getRoot()->getElement("param2")->getComment(), "some comment 2");

    std::string sSaved = "";
    if (yaml.saveToString(sSaved)) {
        compareS(bTestSuccess, "yaml_save", sSaved,
            "# Some comment 1\n"
            "param1: value1 # comment 2 # comment\n"
            "param2: value2 # some \"comment 3\"\n"
            "# Some comment 4\n"
            "array1: # comment 5\n"
            "  - val1 # comment 6\n"
            "  # comment 7\n"
            "  \n"
            "  - val2 # comment 8\n"
            "map1: # comment 9\n"
            "  p1: val 1 # comment 10\n"
            "  # comment 11\n"
            "  p2: val 2 # comment 12"
        );
    } else {
        WSJCppLog::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}