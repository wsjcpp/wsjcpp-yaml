#include <wsjcpp_unit_tests.h>
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestYamlParserQuotes

class UnitTestYamlParserQuotes : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserQuotes();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

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

    std::string sTestYaml = 
        "# Some comment 1\n"
        "param1: \"value1\" # v1\n"
        "param2: \" #$!!!value2\" # val 2\n"
        "\" param3 olala\" : val 3 # val 3*** \n"
        "param4: ' #$!!!value4' # val 4\n"
        "'param5 aha': ' #$!!!value5' # val 5\n"
        "url: \"https://github.com/wsjcpp/wsjcpp-yaml\"\n"
        "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues\n"
        "empty: \"\"\n"
        "array:\n"
        "  - \"https://github.com/wsjcpp/wsjcpp-core:v0.0.1\"\n"
    ;


    
    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("parse_quotes", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    // TODO: .findLine(0)

    compare("param1", yaml.getRoot()->getElement("param1")->getStringValue(), "value1");
    compare("param1", yaml.getRoot()->getElement("param1")->getComment(), "v1");
    
    compare("param2", yaml.getRoot()->getElement("param2")->getStringValue(), " #$!!!value2");
    compare("param2", yaml.getRoot()->getElement("param2")->getComment(), "val 2");

    compare(" param3 olala", yaml.getRoot()->getElement(" param3 olala")->getStringValue(), "val 3");
    compare(" param3 olala", yaml.getRoot()->getElement(" param3 olala")->getComment(), "val 3***");

    compare("param4 val", yaml.getRoot()->getElement("param4")->getStringValue(), " #$!!!value4");
    compare("param4 comment", yaml.getRoot()->getElement("param4")->getStringValue(), " #$!!!value4");

    compare("url-value", yaml.getRoot()->getElement("url")->getStringValue(), "https://github.com/wsjcpp/wsjcpp-yaml");
    compare("issues-value", yaml.getRoot()->getElement("issues")->getStringValue(), "https://github.com/wsjcpp/wsjcpp-yaml/issues");
    compare("empty-value", yaml.getRoot()->getElement("empty")->getStringValue(), "");

    compare("array-element0-value", yaml.getRoot()->getElement("array")->getElement(0)->getStringValue(), "https://github.com/wsjcpp/wsjcpp-core:v0.0.1");

    std::string sSaved = "";
    compare("save yaml", yaml.saveToString(sSaved), true);
    compare("yaml_save", sSaved,
        "# Some comment 1\n"
        "param1: \"value1\" # v1\n"
        "param2: \" #$!!!value2\" # val 2\n"
        "\" param3 olala\": val 3 # val 3***\n"
        "param4: ' #$!!!value4' # val 4\n"
        "'param5 aha': ' #$!!!value5' # val 5\n"
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