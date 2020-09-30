#include <wsjcpp_unit_tests.h>
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestYamlParserSimpleMap

class UnitTestYamlParserSimpleMap : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserSimpleMap();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

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

    std::string sTestYaml = 
        "# Some comment 1\n"
        "param1: value1\n"
        "param2: value2 # some comment 2\n"
        "\n" // empty line
    ;
    
    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("simple_map", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }
    
    WsjcppYamlNode *pItem = nullptr;
    compare("param1", yaml.getRoot()->getElement("param1")->getValue(), "value1");
    compare("param2", yaml.getRoot()->getElement("param2")->getValue(), "value2");
    compare("param2", yaml.getRoot()->getElement("param2")->getComment(), "some comment 2");

    std::string sSaved = "";
    bool bResult = yaml.saveToString(sSaved, sError);
    if (compare("save yaml", bResult, true)) {
        compare("yaml_save", sSaved,
            "# Some comment 1\n"
            "param1: value1\n"
            "param2: value2 # some comment 2\n"
        );
    }
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserSimpleMap::doAfterTest() {
    // nothing
    return true;
}