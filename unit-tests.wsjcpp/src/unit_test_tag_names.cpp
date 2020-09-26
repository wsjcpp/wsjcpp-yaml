
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestTagNames

class UnitTestTagNames : public WsjcppUnitTestBase {
    public:
        UnitTestTagNames();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestTagNames)

UnitTestTagNames::UnitTestTagNames()
    : WsjcppUnitTestBase("UnitTestTagNames") {
}

// ---------------------------------------------------------------------

bool UnitTestTagNames::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestTagNames::executeTest() {

    std::string sTestYaml = "./test10: one";
    WsjcppYaml yaml;
    std::string sError;
    // wrong 
    compare("wrong name", yaml.loadFromString("wrong name", "./test10: one", sError), false);
    compare("name use quotes 1", yaml.loadFromString("name use quotes", "\"./test10\": one", sError), true);
    compare("name use quotes 2 - wrong", yaml.loadFromString("name use quotes", "\"./te\"st10\": one", sError), false);
    compare("name use quotes 3", yaml.loadFromString("name use quotes", "\"./te\\\"st10\": one", sError), true);

    compare("array", yaml.loadFromString("array", 
        "arr1: \n"
        "  - ./te:11\n"
        "  - \"./te\":11\n"
    , sError), true);

    compare("arr1 is array", yaml.getRoot()->getElement("arr1")->isArray(), true);
    compare("arr1 size 2", yaml.getRoot()->getElement("arr1")->getLength(), 2);
    compare("arr1 el 0 is value", yaml.getRoot()->getElement("arr1")->getElement(0)->isValue(), true);
    compare("arr1 el 0 is value", yaml.getRoot()->getElement("arr1")->getElement(0)->getValue(), "./te:11");
    compare("arr1 el 1 is map", yaml.getRoot()->getElement("arr1")->getElement(1)->isMap(), true);
    compare("arr1 el 1 is map", yaml.getRoot()->getElement("arr1")->getElement(1)->hasElement("./te"), true);
    compare("arr1 el 1 is map", yaml.getRoot()->getElement("arr1")->getElement(1)->getElement("./te")->getValue(), "11");
}

// ---------------------------------------------------------------------

bool UnitTestTagNames::doAfterTest() {
    // do somethig after test
    return true;
}


