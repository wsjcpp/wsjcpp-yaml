
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
    std::string sTestYaml = 
        "# Some comment 1\n"
        "   \n"
        "arr1: \n"
        "\n"
        "  - name: i1\n"
        "    var2: 2\n"
        "  - name: i2\n"
        "  - name: i3\n"
        "\n" // empty line
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromString("rm_elem_in_arr", sTestYaml, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    
    WsjcppYamlItem *pArr1 = yaml.getRoot()->getElement("arr1");
    compare("arr1 len", pArr1->getLength(), 3);
    compare("arr1 name0 ", pArr1->getElement(0)->getElement("name")->getStringValue(), "i1");
    compare("arr1 name1 ", pArr1->getElement(1)->getElement("name")->getStringValue(), "i2");
    compare("arr1 name2 ", pArr1->getElement(2)->getElement("name")->getStringValue(), "i3");

    pArr1->removeElement(1);

    compare("arr1 len", pArr1->getLength(), 2);
    compare("arr1 name0 ", pArr1->getElement(0)->getElement("name")->getStringValue(), "i1");
    compare("arr1 name1 ", pArr1->getElement(1)->getElement("name")->getStringValue(), "i3");
}

// ---------------------------------------------------------------------

bool UnitTestRemoveElementInArray::doAfterTest() {
    // do somethig after test
    return true;
}


