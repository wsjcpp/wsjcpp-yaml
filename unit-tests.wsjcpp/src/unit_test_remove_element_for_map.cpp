
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestRemoveElementForMap

class UnitTestRemoveElementForMap : public WsjcppUnitTestBase {
    public:
        UnitTestRemoveElementForMap();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestRemoveElementForMap)

UnitTestRemoveElementForMap::UnitTestRemoveElementForMap()
    : WsjcppUnitTestBase("UnitTestRemoveElementForMap") {
}

// ---------------------------------------------------------------------

bool UnitTestRemoveElementForMap::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestRemoveElementForMap::executeTest() {
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
        "\n" // empty line
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("rm_elem_in_map", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    WsjcppYamlNode *pMap1 = yaml.getRoot()->getElement("map1");
    WsjcppYamlNode *pMap11 = pMap1->getElement("map11");

    compare("has map111", pMap11->hasElement("map111"), true);
    compare("has map112", pMap11->hasElement("map112"), true);
    compare("has map113", pMap11->hasElement("map113"), true);
    pMap11->removeElement("map112");

    compare("has map111", pMap11->hasElement("map111"), true);
    compare("has map112", pMap11->hasElement("map112"), false);
    compare("has map113", pMap11->hasElement("map113"), true);
    pMap11->removeElement("map111");

    compare("has map111", pMap11->hasElement("map111"), false);
    compare("has map112", pMap11->hasElement("map112"), false);
    compare("has map113", pMap11->hasElement("map113"), true);

    compare("has map11", pMap1->hasElement("map11"), true);
    yaml.getRoot()->getElement("map1")->removeElement("map11");
    compare("has map11", pMap1->hasElement("map11"), false);
}

// ---------------------------------------------------------------------

bool UnitTestRemoveElementForMap::doAfterTest() {
    // do somethig after test
    return true;
}


