
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestReadYaml

class UnitTestReadYaml : public WsjcppUnitTestBase {
    public:
        UnitTestReadYaml();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestReadYaml)

UnitTestReadYaml::UnitTestReadYaml()
    : WsjcppUnitTestBase("UnitTestReadYaml") {
}

// ---------------------------------------------------------------------

bool UnitTestReadYaml::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestReadYaml::executeTest() {
    WsjcppYaml yaml;
    std::string sFilepath = "./data-tests/read-file/example-voiting-app/docker-compose.yml";
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    compare("has version", yaml.getRoot()->hasElement("version"), true);
    compare("has volumes", yaml.getRoot()->hasElement("volumes"), true);
    compare("has networks", yaml.getRoot()->hasElement("networks"), true);
    compare("has services", yaml.getRoot()->hasElement("services"), true);

    compare("version-value", yaml.getRoot()->getElement("version")->getStringValue(), "3");
    compare("version-value", yaml.getRoot()->getElement("version")->getIntValue(), 3); // wrong or not ?

    // TODO unit test source code here
}

// ---------------------------------------------------------------------

bool UnitTestReadYaml::doAfterTest() {
    // do somethig after test
    return true;
}


