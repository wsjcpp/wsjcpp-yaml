
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestCursor

class UnitTestCursor : public WsjcppUnitTestBase {
    public:
        UnitTestCursor();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestCursor)

UnitTestCursor::UnitTestCursor()
    : WsjcppUnitTestBase("UnitTestCursor") {
}

// ---------------------------------------------------------------------

bool UnitTestCursor::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestCursor::executeTest() {

     std::string sTestYaml = 
        "# Some comment 1\n"
        "map1: \n"
        "  map11: \n"
        "    map111: \n"
        "      param1111: v1111\n"
        "      param1112: v1112\n"
        "    map112: \n"
        "      param1121: v1121\n"
        "      param1122: v1122\n"
        "    map113: \n"
        "      param1131: v1131\n"
        "      param1132: v1132\n"
        "  map12: \n"
        "    param121: v121\n"
        "    param122: v122\n"
        "    map123: \n"
        "      param1231: v1231\n"
        "      param1232: v1232\n"
        "param2: v2 # some comment 2\n"
        "arr1: # some comment 2\n"
        "  - some1\n"
        "  - some2\n"
        "  - some3\n"
        "\n" // empty line
    ;
    
    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("test_cursor", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    compare("map1 is null", yaml["map1"].isNull(), false);
    compare("map1 is array", yaml["map1"].isArray(), false);
    compare("map1 is map", yaml["map1"].isMap(), true);

    compare("map1-1111 is null", yaml["map1-1111"].isNull(), true);
    compare("map1-1111 is array", yaml["map1-1111"].isArray(), false);
    compare("map1-1111 is map", yaml["map1-1111"].isMap(), false);

    compare("arr1 is null", yaml["arr1"].isNull(), false);
    compare("arr1 is array", yaml["arr1"].isArray(), true);
    compare("arr1 is map", yaml["arr1"].isMap(), false);
    

    compare("map use as array", yaml["map1"][0].isNull(), true);
    compare("array use as map", yaml["arr1"]["0"].isNull(), true);

}

// ---------------------------------------------------------------------

bool UnitTestCursor::doAfterTest() {
    // do somethig after test
    return true;
}


