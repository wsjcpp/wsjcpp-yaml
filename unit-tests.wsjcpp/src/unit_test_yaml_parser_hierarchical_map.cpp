#include <wsjcpp_unit_tests.h>
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestYamlParserHierarchicalMap

class UnitTestYamlParserHierarchicalMap : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserHierarchicalMap();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestYamlParserHierarchicalMap)

UnitTestYamlParserHierarchicalMap::UnitTestYamlParserHierarchicalMap()
    : WsjcppUnitTestBase("UnitTestYamlParserHierarchicalMap") {
    //
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserHierarchicalMap::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestYamlParserHierarchicalMap::executeTest() {

    std::string sTestYaml = 
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
    
    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("hard_map", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }
    
    WsjcppYamlNode *pItem = nullptr;

    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map111");
    compare("param1111", pItem->getElement("param1111")->getValue(), "v1111");
    compare("param1112", pItem->getElement("param1112")->getValue(), "v1112");
    
    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map112");
    compare("param1121", pItem->getElement("param1121")->getValue(), "v1121");
    compare("param1122", pItem->getElement("param1122")->getValue(), "v1122");
    
    pItem = yaml.getRoot()->getElement("map1")->getElement("map11")->getElement("map113");
    compare("param1131", pItem->getElement("param1131")->getValue(), "v1131");
    compare("param1132", pItem->getElement("param1132")->getValue(), "v1132");

    pItem = yaml.getRoot()->getElement("map1")->getElement("map12");
    compare("param121", pItem->getElement("param121")->getValue(), "v121");
    compare("param122", pItem->getElement("param122")->getValue(), "v122");

    pItem = yaml.getRoot()->getElement("map1")->getElement("map12")->getElement("map123");
    compare("param1231", pItem->getElement("param1231")->getValue(), "v1231");
    compare("param1232", pItem->getElement("param1232")->getValue(), "v1232");

    compare("param2", yaml.getRoot()->getElement("param2")->getValue(), "v2");
    compare("param2", yaml.getRoot()->getElement("param2")->getComment(), "some comment 2");

    std::string sSaved = "";
    bool bResult = yaml.saveToString(sSaved, sError);
    if (compare("save yaml", bResult, true)) {
        compare("yaml_save", sSaved,
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
            "param2: v2 # some comment 2\n"
        );
    }
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserHierarchicalMap::doAfterTest() {
    // nothing
    return true;
}