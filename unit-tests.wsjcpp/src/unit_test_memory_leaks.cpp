
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>
#include "get_current_rss.h"
#include "process_mem_usage.h"


// ---------------------------------------------------------------------
// UnitTestMemoryLeaks

class UnitTestMemoryLeaks : public WsjcppUnitTestBase {
    public:
        UnitTestMemoryLeaks();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestMemoryLeaks)

UnitTestMemoryLeaks::UnitTestMemoryLeaks()
    : WsjcppUnitTestBase("UnitTestMemoryLeaks") {
}

// ---------------------------------------------------------------------

bool UnitTestMemoryLeaks::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestMemoryLeaks::executeTest() {
    double nBeforeVm, nBeforeRss;
    double nAfterVm, nAfterRss;
    std::string sFilepath = "./data-tests/for-memory-leak/some.yml";
    std::string sError;

    // std::cout << "currentSize "<< getCurrentRSS() << std::endl;
    // std::cout << "peakSize "<< getPeakRSS() << std::endl;
   
    // first use for memory alloc some
    for (int i = 0; i < 1000; i++) {
        WsjcppYaml yaml;
        if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
            WsjcppLog::err(TAG, sError);
            return;
        }
    }
    
    process_mem_usage(nBeforeVm, nBeforeRss);
    // std::cout << "nBeforeVm: " << nBeforeVm << std::endl;
    // std::cout << "nBeforeRss: " << nBeforeRss << std::endl;
    compare("memory vm not null", (int)nBeforeVm > 0, true);
    compare("memory vm not null", (int)nBeforeRss > 0, true);

    // std::cout << "currentSize "<< getCurrentRSS() << std::endl;
    // std::cout << "peakSize "<< getPeakRSS() << std::endl;

    // code again check the memoty leak

    for (int i = 0; i < 1000; i++) {
        WsjcppYaml yaml;
        if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
            WsjcppLog::err(TAG, sError);
            return;
        }
    }

    process_mem_usage(nAfterVm, nAfterRss);
    // std::cout << "nAfterVm: " << nAfterVm << std::endl;
    // std::cout << "nAfterRss: " << nAfterRss << std::endl;
    compare("memory vm", (int)nAfterVm, (int)nBeforeVm);
    compare("memory rss", (int)nAfterRss, (int)nBeforeRss);
    // std::cout << "currentSize "<< getCurrentRSS() << std::endl;
    // std::cout << "peakSize "<< getPeakRSS() << std::endl;
}

// ---------------------------------------------------------------------

bool UnitTestMemoryLeaks::doAfterTest() {
    // do somethig after test
    return true;
}


