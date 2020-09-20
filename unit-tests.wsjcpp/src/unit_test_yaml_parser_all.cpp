#include <wsjcpp_unit_tests.h>
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestYamlParserAll

class UnitTestYamlParserAll : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserAll();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};


REGISTRY_WSJCPP_UNIT_TEST(UnitTestYamlParserAll)

UnitTestYamlParserAll::UnitTestYamlParserAll()
    : WsjcppUnitTestBase("UnitTestYamlParserAll") {
    //
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserAll::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestYamlParserAll::executeTest() {

    std::string sTestYaml = 
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

    WsjcppYaml yaml;
    if (!compare("Error parsing", yaml.loadFromString(sTestYaml), true)) {
        return;
    }

    std::string sSaved1 = "";
    if (!compare("Error saving", yaml.saveToString(sSaved1), true)) {
        compare("yaml_saved 2-test", sSaved1, sTestYaml);
        return;
    }
    
    WsjcppYamlItem *pItem = nullptr;
    compare("test10", yaml.getRoot()->getElement("test10")->getValue(), "one");
    compare("test20", yaml.getRoot()->getElement("test20")->getValue(), "two");
        
    pItem = yaml.getRoot()->getElement("array30");
    compare("array30_length", pItem->getLength(), 3);

    pItem = yaml.getRoot()->getElement("array30")->getElement(0);
    compare("test30_value", pItem->getValue(), "one31");
    compare("test30_comment", pItem->getComment(), "this field for test array30");
    pItem = yaml.getRoot()->getElement("array30")->getElement(1);
    compare("test40_value", pItem->getValue(), "two32");
    compare("test40_comment", pItem->getComment(), "");

    pItem = yaml.getRoot()->getElement("array40");
    compare("array40_length", pItem->getLength(), 2);

    pItem = yaml.getRoot()->getElement("array50");
    compare("array50_length", pItem->getLength(), 2);
    
    pItem = yaml.getRoot()->getElement("map60")->getElement("test70");
    compare("test70_value", pItem->getValue(), "opa1");

    pItem = yaml.getRoot()->getElement("map60")->getElement("test80");
    compare("test80_comment", pItem->getValue(), "opa2");

    std::string sSaved2 = "";
    if (compare("saving yaml", yaml.saveToString(sSaved2), true)) {
        compare("yaml_saved 1-2", sSaved1, sSaved2);
    }
}

// ---------------------------------------------------------------------

bool UnitTestYamlParserAll::doAfterTest() {
    // do something after test
    return true;
}
