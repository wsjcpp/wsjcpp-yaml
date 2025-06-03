
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestFloatDouble

class UnitTestFloatDouble : public WsjcppUnitTestBase {
    public:
        UnitTestFloatDouble();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestFloatDouble)

UnitTestFloatDouble::UnitTestFloatDouble()
    : WsjcppUnitTestBase("UnitTestFloatDouble") {
}

// ---------------------------------------------------------------------

bool UnitTestFloatDouble::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestFloatDouble::executeTest() {
    WsjcppYaml yaml;
    std::string sFilepath = "./data-tests/read-file/float-double/example.yml";
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    compare("has float field ", yaml.getRoot()->hasElement("float"), true);
    compare("has float field is value", yaml.getRoot()->getElement("float")->isValue(), true);
    compare("has float value is 1.0001 (str)", yaml.getRoot()->getElement("float")->getValue(), "1.0001");
    compare("has float value is 1.0001 (float)", yaml["float"].valFloat(), 1.0001f);

    compare("has double field ", yaml.getRoot()->hasElement("double"), true);
    compare("has double field is value", yaml.getRoot()->getElement("double")->isValue(), true);
    compare("has double value is 1.0002 (str)", yaml.getRoot()->getElement("double")->getValue(), "1.0002");
    compare("has double value is 1.0002 (double)", yaml["double"].valFloat(), 1.0002f);

    yaml["double"].val(1.0003f);
    compare("has double value is 1.0003 (str)", yaml.getRoot()->getElement("double")->getValue(), "1.0003");
    compareD("has double value is 1.0003 (double 1)", yaml["double"].valFloat(), 1.0003f);
    compareD("has double value is 1.0003 (double 2)", yaml["double"].valDouble(), 1.0003f);
}

// ---------------------------------------------------------------------

bool UnitTestFloatDouble::doAfterTest() {
    // do somethig after test
    return true;
}


