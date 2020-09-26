
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_core.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestRemoveElementInArray

class UnitTestRemoveElementInArray : public WsjcppUnitTestBase {
    public:
        UnitTestRemoveElementInArray();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestRemoveElementInArray)

UnitTestRemoveElementInArray::UnitTestRemoveElementInArray()
    : WsjcppUnitTestBase("UnitTestRemoveElementInArray") {
}

// ---------------------------------------------------------------------

bool UnitTestRemoveElementInArray::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestRemoveElementInArray::executeTest() {

    std::string sFilepath = "./data-tests/remove-element-in-array.yml";
    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    
    WsjcppYamlNode *pArr1 = yaml.getRoot()->getElement("arr1");
    compare("arr1 len", pArr1->getLength(), 4);
    compare("arr1 name0 ", pArr1->getElement(0)->getElement("name")->getValue(), "i1");
    compare("arr1 name1 ", pArr1->getElement(1)->getElement("name")->getValue(), "i2");
    compare("arr1 name2 ", pArr1->getElement(2)->getElement("name")->getValue(), "i3");
    compare("arr1 name3 ", pArr1->getElement(3)->getValue(), "very different array items type");

    pArr1->removeElement(1);

    compare("arr1 len", pArr1->getLength(), 3);
    compare("arr1 name0 ", pArr1->getElement(0)->getElement("name")->getValue(), "i1");
    compare("arr1 name1 ", pArr1->getElement(1)->getElement("name")->getValue(), "i3");
    compare("arr1 name2 ", pArr1->getElement(2)->getValue(), "very different array items type");
}

// ---------------------------------------------------------------------

bool UnitTestRemoveElementInArray::doAfterTest() {
    // do somethig after test
    return true;
}


