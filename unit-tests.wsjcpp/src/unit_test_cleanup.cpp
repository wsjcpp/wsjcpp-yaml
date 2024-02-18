
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestCleanup

class UnitTestCleanup : public WsjcppUnitTestBase {
    public:
        UnitTestCleanup();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestCleanup)

UnitTestCleanup::UnitTestCleanup()
    : WsjcppUnitTestBase("UnitTestCleanup") {
}

// ---------------------------------------------------------------------

bool UnitTestCleanup::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestCleanup::executeTest() {
    std::string sTestYaml1 =
        "# Some comment 1\n"
        "test10: one\n"
        "test20: two # some comment 2\n"
    ;

    std::string sTestYaml2 =
        "# Some comment 1\n"
        "test11: one\n"
        "test20: two # some comment 2\n"
        "test22: two # some comment 2\n"
    ;

    WsjcppYaml yaml;
    std::string sError;

    if (!compare("Error parsing 1", yaml.loadFromString("parse1", sTestYaml1, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    compare("(1) has test10", yaml.getRoot()->hasElement("test10"), true);
    compare("(1) has test11", yaml.getRoot()->hasElement("test11"), false);
    compare("(1) has test20", yaml.getRoot()->hasElement("test20"), true);
    compare("(1) has test22", yaml.getRoot()->hasElement("test22"), false);

    if (!compare("Error parsing 2", yaml.loadFromString("parse2", sTestYaml2, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    compare("(2) has test10", yaml.getRoot()->hasElement("test10"), false);
    compare("(2) has test11", yaml.getRoot()->hasElement("test11"), true);
    compare("(2) has test20", yaml.getRoot()->hasElement("test20"), true);
    compare("(2) has test22", yaml.getRoot()->hasElement("test22"), true);

    yaml.clear();

    compare("(3) has root", yaml.getRoot() == nullptr, true);
}

// ---------------------------------------------------------------------

bool UnitTestCleanup::doAfterTest() {
    // do somethig after test
    return true;
}


