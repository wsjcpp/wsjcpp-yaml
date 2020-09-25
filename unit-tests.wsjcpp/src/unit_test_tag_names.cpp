
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
    compare("name use quotes", yaml.loadFromString("name use quotes", "\"./test10\": one", sError), true);

}

// ---------------------------------------------------------------------

bool UnitTestTagNames::doAfterTest() {
    // do somethig after test
    return true;
}


