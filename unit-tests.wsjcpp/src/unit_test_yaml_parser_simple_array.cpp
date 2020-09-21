#include <wsjcpp_unit_tests.h>
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestYamlParserSimpleArray

class UnitTestYamlParserSimpleArray : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserSimpleArray();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestYamlParserSimpleArray)

UnitTestYamlParserSimpleArray::UnitTestYamlParserSimpleArray()
    : WsjcppUnitTestBase("UnitTestYamlParserSimpleArray") {
    //
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserSimpleArray::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestYamlParserSimpleArray::executeTest() {

    std::string sTestYaml = 
        "# simple array test\n"
        "param1: none value1 # it's value for something # olala  \n"
        "array-test2 : #    some comment 2   \n"
        "  - value21 # comment v21 \n"
        "  - value22 # comment v22 \n"
        "  - true # comment true \n"
        "  # some\n"
        "  - falsesome   \n"
        "  - free@free   \n"
        "  - # empty \n"
        "  - 1\n"
        "param2: val2 #  value 2 \n"
    ;
    
    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("parse_array", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }
    
    WsjcppYamlItem *pItem = nullptr;

    compare("param1-value", yaml.getRoot()->getElement("param1")->getValue(), "none value1");
    compare("param1-line", yaml.getRoot()->getElement("param1")->getPlaceInFile().getLine(), "param1: none value1 # it's value for something # olala  ");
    compare("param1-original-number-of-line", yaml.getRoot()->getElement("param1")->getPlaceInFile().getNumberOfLine(), 1);
    compare("param1-comment", yaml.getRoot()->getElement("param1")->getComment(), "it's value for something # olala");

    compare("array-test2-length", yaml.getRoot()->getElement("array-test2")->getLength(), 7);
    compare("array-test2-comment", yaml.getRoot()->getElement("array-test2")->getComment(), "some comment 2");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(0);
    compare("array-test2-element0-value", pItem->getValue(), "value21");
    compare("array-test2-element0-comment", pItem->getComment(), "comment v21");

    pItem = yaml.getRoot()->getElement("array-test2")->getElement(1);
    compare("array-test2-element1-value", pItem->getValue(), "value22");
    compare("array-test2-element1-comment", pItem->getComment(), "comment v22");

    compare("array-test2-element2-value", yaml["array-test2"][2].getValue(), "true");
    compare("array-test2-element2-line", yaml["array-test2"][2].getPlaceInFile().getLine(), "  - true # comment true ");
    compare("array-test2-element2-original-number-of-line", yaml["array-test2"][2].getPlaceInFile().getNumberOfLine(), 5);
    compare("array-test2-element2-comment", yaml["array-test2"][2].getComment(), "comment true");

    compare("array-test2-element3-value", yaml["array-test2"][3].getValue(), "falsesome");
    compare("array-test2-element3-line", yaml["array-test2"][3].getPlaceInFile().getLine(), "  - falsesome   ");
    compare("array-test2-element3-original-number-of-line", yaml["array-test2"][3].getPlaceInFile().getNumberOfLine(), 7);
    compare("array-test2-element3-comment", yaml["array-test2"][3].getComment(), "");
    
    compare("array-test2-element4-value", yaml["array-test2"][4].getValue(), "free@free");
    compare("array-test2-element4-line", yaml["array-test2"][4].getPlaceInFile().getLine(), "  - free@free   ");
    compare("array-test2-element4-original-number-of-line", yaml["array-test2"][4].getPlaceInFile().getNumberOfLine(), 8);
    compare("array-test2-element4-comment", yaml["array-test2"][4].getComment(), "");

    compare("array-test2-element5-value", yaml["array-test2"][5].getValue(), "");
    compare("array-test2-element5-line", yaml["array-test2"][5].getPlaceInFile().getLine(), "  - # empty ");
    compare("array-test2-element5-original-number-of-line", yaml["array-test2"][5].getPlaceInFile().getNumberOfLine(), 9);
    compare("array-test2-element5-comment", yaml["array-test2"][5].getComment(), "empty");

    compare("array-test2-element6-value", yaml["array-test2"][6].getValue(), "1");
    compare("array-test2-element6-line", yaml["array-test2"][6].getPlaceInFile().getLine(), "  - 1");
    compare("array-test2-element6-original-number-of-line", yaml["array-test2"][6].getPlaceInFile().getNumberOfLine(), 10);
    compare("array-test2-element6-comment", yaml["array-test2"][6].getComment(), "");

    compare("param2-value", yaml.getRoot()->getElement("param2")->getValue(), "val2");
    compare("param2-line", yaml.getRoot()->getElement("param2")->getPlaceInFile().getLine(), "param2: val2 #  value 2 ");
    compare("param2-original-number-of-line", yaml.getRoot()->getElement("param2")->getPlaceInFile().getNumberOfLine(), 11);
    compare("param2-comment", yaml.getRoot()->getElement("param2")->getComment(), "value 2");

    std::string sSaved = "";
    bool bResult = yaml.saveToString(sSaved);
    compare("save yaml", bResult, true);
    compare("yaml_save", sSaved, 
        "# simple array test\n" // expected
        "param1: none value1 # it's value for something # olala\n"
        "array-test2: # some comment 2\n"
        "  - value21 # comment v21\n"
        "  - value22 # comment v22\n"
        "  - true # comment true\n"
        "  # some\n"
        "  - falsesome\n"
        "  - free@free\n"
        "  - # empty\n"
        "  - 1\n"
        "param2: val2 # value 2"
    );
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserSimpleArray::doAfterTest() {
    // nothing
    return true;
}