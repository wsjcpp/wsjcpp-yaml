#include "unit_test_yaml_parser_all.h"
#include <vector>
#include <iostream>
#include <wsjcpp_core.h>
#include <wsjcpp_yaml.h>

REGISTRY_UNIT_TEST(UnitTestYamlParserAll)

UnitTestYamlParserAll::UnitTestYamlParserAll()
    : UnitTestBase("UnitTestYamlParserAll") {
    //
}

// ---------------------------------------------------------------------

void UnitTestYamlParserAll::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserAll::run() {

    std::string g_sTestYaml = 
        "# Some comment 1\n"
        "test10: one\n"
        "test20: two # some comment 2\n"
        "\n" // empty line
        "array30:\n"
        "  - one31 # this field for test array30\n"
        "  - two32\n"
        "  - three33\n"
        "\n" // empty line
        "array40: # some comment 3\n"
        "  - \"one#1\" # some comment\n"
        "  # some comment\n"
        "  - \"two#2\"\n"
        "array50: # some comment 3\n"
        "  - p1: test501\n"
        "    p2: test502\n"
        "  - p1: test503\n"
        "    p2: test504\n"
        "\n" // empty line
        "map60: # some comment 4\n"
        "  test70: opa1\n"
        "  test80: opa2"
    ;

    bool bTestSuccess = true;
    
    WSJCppYAML yaml;
    if (yaml.loadFromString(g_sTestYaml)) {
        WSJCppLog::throw_err(TAG, "Error parsing");
        return -1;
    }
    std::string sSaved = "";
    if (yaml.saveToString(sSaved)) {
        WSJCppLog::info(TAG, "\n>>>>\n" + sSaved);
    }
    
    WSJCppYAMLItem *pItem = nullptr;
    compareS(bTestSuccess, "test10", yaml.getRoot()->getElement("test10")->getValue(), "two");
    compareS(bTestSuccess, "test20", yaml.getRoot()->getElement("test20")->getValue(), "two");
        
    pItem = yaml.getRoot()->getElement("array30");
    compareN(bTestSuccess, "array30_length", pItem->getLength(), 3);

    pItem = yaml.getRoot()->getElement("array30")->getElement(0);
    compareS(bTestSuccess, "test30_value", pItem->getValue(), "one31");
    compareS(bTestSuccess, "test30_comment", pItem->getComment(), "this field for test array30");
    pItem = yaml.getRoot()->getElement("array30")->getElement(1);
    compareS(bTestSuccess, "test40_value", pItem->getValue(), "two32");
    compareS(bTestSuccess, "test40_comment", pItem->getComment(), "");

    pItem = yaml.getRoot()->getElement("array40");
    compareN(bTestSuccess, "array40_length", pItem->getLength(), 2);

    pItem = yaml.getRoot()->getElement("array50");
    compareN(bTestSuccess, "array50_length", pItem->getLength(), 1);
    
    pItem = yaml.getRoot()->getElement("map60")->getElement("test70");
    compareS(bTestSuccess, "test70_value", pItem->getValue(), "opa1");

    pItem = yaml.getRoot()->getElement("map60")->getElement("test80");
    compareS(bTestSuccess, "test80_comment", pItem->getValue(), "opa2");

    sSaved = "";
    if (yaml.saveToString(sSaved)) {
        compareS(bTestSuccess, "yaml_save", sSaved, g_sTestYaml);
    } else {
        WSJCppLog::err(TAG, "Could not save to string");
        bTestSuccess = false;
    }
    return bTestSuccess;
}