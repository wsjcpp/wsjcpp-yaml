
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp/yaml/yaml.h>

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
        "    sss: \n"
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
        "    param1232: v1232\n"
        "param2: v2 # some comment 2\n"
        "arr1: # some comment array 1\n"
        "  - some1\n"
        "  - 3\n"
        "\n"
        "  - Yes\n"
        "  # empty\n"
        "  - no\n"
        "  - true\n"
        "  - False\n"
        "\n" // empty line
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("test_cursor", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    compare("map1 is null", yaml["map1"].isNull(), false);
    compare("map1 is undefined", yaml["map1"].isUndefined(), false);
    compare("map1 is value", yaml["map1"].isValue(), false);
    compare("map1 is array", yaml["map1"].isArray(), false);
    compare("map1 is map", yaml["map1"].isMap(), true);

    compare("map1-1111 is null", yaml["map1-1111"].isNull(), true);
    compare("map1 is undefined", yaml["map1-1111"].isUndefined(), false);
    compare("map1 is value", yaml["map1-1111"].isValue(), false);
    compare("map1-1111 is array", yaml["map1-1111"].isArray(), false);
    compare("map1-1111 is map", yaml["map1-1111"].isMap(), false);

    compare("arr1 is null", yaml["arr1"].isNull(), false);
    compare("arr1 is undefined", yaml["arr1"].isUndefined(), false);
    compare("arr1 is value", yaml["arr1"].isValue(), false);
    compare("arr1 is array", yaml["arr1"].isArray(), true);
    compare("arr1 is map", yaml["arr1"].isMap(), false);

    compare("map1.map11.sss is null", yaml["map1"]["map11"]["sss"].isNull(), false);
    compare("map1.map11.sss is undefined", yaml["map1"]["map11"]["sss"].isUndefined(), true);
    compare("map1.map11.sss is value", yaml["map1"]["map11"]["sss"].isValue(), false);
    compare("map1.map11.sss is array", yaml["map1"]["map11"]["sss"].isArray(), false);
    compare("map1.map11.sss is map", yaml["map1"]["map11"]["sss"].isMap(), false);

    compare("map1.map11.map111.param1111 is null", yaml["map1"]["map11"]["map111"]["param1111"].isNull(), false);
    compare("map1.map11.map111.param1111 is undefined", yaml["map1"]["map11"]["map111"]["param1111"].isUndefined(), false);
    compare("map1.map11.map111.param1111 is value", yaml["map1"]["map11"]["map111"]["param1111"].isValue(), true);
    compare("map1.map11.map111.param1111 is array", yaml["map1"]["map11"]["map111"]["param1111"].isArray(), false);
    compare("map1.map11.map111.param1111 is map", yaml["map1"]["map11"]["map111"]["param1111"].isMap(), false);

    compare("map use as array", yaml["map1"][0].isNull(), true);
    compare("array use as map", yaml["arr1"]["0"].isNull(), true);
    compare("array use as array", yaml["arr1"][0].isNull(), false);

    compare("array size", yaml["arr1"].comment(), "some comment array 1");
    compare("array size", yaml["arr1"].size(), 6);
    compare("array el 0", yaml["arr1"][0].valStr(), "some1");
    compare("array el 1", yaml["arr1"][1].valStr(), "3");
    compare("array el 2", yaml["arr1"][2].valStr(), "Yes");
    compare("array el 3", yaml["arr1"][3].valStr(), "no");
    compare("array el 4", yaml["arr1"][4].valStr(), "true");
    compare("array el 5", yaml["arr1"][5].valStr(), "False");

    compare("array bool el 2", yaml["arr1"][2].valBool(), true);
    compare("array bool el 3", yaml["arr1"][3].valBool(), false);
    compare("array bool el 4", yaml["arr1"][4].valBool(), true);
    compare("array bool el 5", yaml["arr1"][5].valBool(), false);

    // int
    compare("array size", yaml["arr1"][1].valInt(), 3);
    yaml["arr1"][1].val(10);
    compare("array size", yaml["arr1"][1].valInt(), 10);

    // string
    compare("array el 0 - 1", yaml["arr1"][0].valStr(), "some1");
    yaml["arr1"][0].val("different value").comment("1234");
    compare("array el 0 - 2", yaml["arr1"][0].valStr(), "different value");
    compare("array el 0 - 3", yaml["arr1"][0].comment(), "1234");

    // bool
    compare("array bool el 4", yaml["arr1"][4].valStr(), "true");
    compare("array bool el 4", yaml["arr1"][4].node()->getValue(), "true");
    compare("array bool el 4", yaml["arr1"][4].valBool(), true);
    yaml["arr1"][4].val(true);
    compare("array bool el 4", yaml["arr1"][4].valStr(), "yes");
    compare("array bool el 4", yaml["arr1"][4].valBool(), true);
    yaml["arr1"][4].val(false);
    compare("array bool el 4", yaml["arr1"][4].valStr(), "no");
    compare("array bool el 4", yaml["arr1"][4].valBool(), false);

    // map
    compare("map1.map12", yaml["map1"]["map12"].isMap(), true);

    std::vector<std::string> vKeys = yaml["map1"]["map12"].keys();
    compare("map1.map12 keys size", vKeys.size(), 4);
    if (vKeys.size() == 4) {
        compare("map1.map12 keys 0", vKeys[0], "param121");
        compare("map1.map12 keys 1", vKeys[1], "param122");
        compare("map1.map12 keys 2", vKeys[2], "map123");
        compare("map1.map12 keys 3", vKeys[3], "param1232");
    }
    compare("map1.map12 has key1", yaml["map1"]["map12"].hasKey("some"), false);
    compare("map1.map12 has key2", yaml["map1"]["map12"].hasKey("map123"), true);
    compare("map1.map12 is value", yaml["map1"]["map12"]["map123"].isValue(), false);
    compare("map1.map12 is value", yaml["map1"]["map12"]["param122"].isValue(), true);


    /*    WsjcppYamlCursor &push(const std::string &sVal);
        WsjcppYamlCursor &push(int nVal);
        WsjcppYamlCursor &push(bool bVal);
        WsjcppYamlCursor &remove(int nIdx);*/


}

// ---------------------------------------------------------------------

bool UnitTestCursor::doAfterTest() {
    // do somethig after test
    return true;
}


