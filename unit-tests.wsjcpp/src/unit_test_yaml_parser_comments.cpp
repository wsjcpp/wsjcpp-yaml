#include <wsjcpp_unit_tests.h>
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestYamlParserComments

class UnitTestYamlParserComments : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserComments();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestYamlParserComments)

UnitTestYamlParserComments::UnitTestYamlParserComments()
    : WsjcppUnitTestBase("UnitTestYamlParserComments") {
    //
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserComments::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestYamlParserComments::executeTest() {

    std::string sTestYaml = 
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


    
    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("comments", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    // TODO: .findLine(0)

    compare("param1", yaml["param1"].getStringValue(), "value1");
    compare("param1", yaml["param1"].getComment(), "comment 2 # comment");
    
    compare("param2", yaml["param2"].getStringValue(), "value2");
    compare("param2", yaml["param2"].getComment(), "some \"comment 3\"");


    compare("array1-comment", yaml["array1"].getComment(), "comment 5");
    compare("array1-length", yaml["array1"].getLength(), 2);
    compare("array1-element0-value", yaml["array1"][0].getStringValue(), "val1");
    compare("array1-element0-comment", yaml["array1"][0].getComment(), "comment 6");

    // TODO: .findLine(7)

    compare("array1-element1-value", yaml["array1"][1].getStringValue(), "val2");
    compare("array1-element1-comment", yaml["array1"][1].getComment(), "comment 8");

    compare("map1-comment", yaml["map1"].getComment(), "comment 9");
    compare("map1-p1-comment", yaml["map1"]["p1"].getComment(), "comment 10");
    compare("map1-p2-comment", yaml["map1"]["p2"].getComment(), "comment 12");

    
    // compare("param2", yaml.getRoot()->getElement("param2")->getStringValue(), "value2");
    // compare("param2", yaml.getRoot()->getElement("param2")->getComment(), "some comment 2");

    std::string sSaved = "";
    compare("save yaml", yaml.saveToString(sSaved), true);
    compare("yaml_save", sSaved,
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
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserComments::doAfterTest() {
    // nothing
    return true;
}
