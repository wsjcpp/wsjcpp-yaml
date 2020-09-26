
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestAppendElements

class UnitTestAppendElements : public WsjcppUnitTestBase {
    public:
        UnitTestAppendElements();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestAppendElements)

UnitTestAppendElements::UnitTestAppendElements()
    : WsjcppUnitTestBase("UnitTestAppendElements") {
}

// ---------------------------------------------------------------------

bool UnitTestAppendElements::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestAppendElements::executeTest() {

    WsjcppYaml yml;
    yml.getRoot()->setElementValue("p1", "val1");
    yml.getRoot()->createElementMap("some");
    WsjcppYamlNode *pSome = yml.getRoot()->getElement("some");
    pSome->setElementValue("p2", "val2");
    pSome->createElementMap("sub-some");
    WsjcppYamlNode *pSubSome = pSome->getElement("sub-some");
    pSubSome->setElementValue("p3", "val3");
    pSome->createElementArray("arr-some");
    WsjcppYamlNode *pArrSome = pSome->getElement("arr-some");
    pArrSome->appendElementValue("1234");
    WsjcppYamlPlaceInFile placeInFile;
    WsjcppYamlNode *pItemMap = new WsjcppYamlNode(pArrSome, placeInFile, WSJCPP_YAML_NODE_MAP);
    pArrSome->appendElement(pItemMap);
    pItemMap->setElementValue("p4", "val4");
    pItemMap->setElementValue("p5", "val5");
    yml.getRoot()->setElementValue("p6", "val6");

    compare("created yaml 1", yml.getRoot()->toString(), 
        "p1: val1\n"
        "some:\n"
        "  p2: val2\n"
        "  sub-some:\n"
        "    p3: val3\n"
        "  arr-some:\n"
        "    - 1234\n"
        "    - p4: val4\n"
        "      p5: val5\n"
        "p6: val6"
    );
}

// ---------------------------------------------------------------------

bool UnitTestAppendElements::doAfterTest() {
    // do somethig after test
    return true;
}


