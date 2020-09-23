
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <wsjcpp_yaml.h>
#include <chrono>
#include <thread>

//////////////////////////////////////////////////////////////////////////////
//
// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in KB.
//
// On failure, returns 0.0, 0.0

void process_mem_usage(double& vm_usage, double& resident_set)
{
   using std::ios_base;
   using std::ifstream;
   using std::string;

   vm_usage     = 0.0;
   resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}

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

    process_mem_usage(nBeforeVm, nBeforeRss);
    // std::cout << "nBeforeVm: " << nBeforeVm << std::endl;
    // std::cout << "nBeforeRss: " << nBeforeRss << std::endl;
    compare("memory vm not null", (int)nBeforeVm > 0, true);
    compare("memory vm not null", (int)nBeforeRss > 0, true);

    for (int i = 0; i < 1000; i++) {
        WsjcppYaml yaml;
        if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
            WsjcppLog::err(TAG, sError);
            return;
        }
    }
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    process_mem_usage(nAfterVm, nAfterRss);
    // std::cout << "nAfterVm: " << nAfterVm << std::endl;
    // std::cout << "nAfterRss: " << nAfterRss << std::endl;
    compare("memory vm", (int)nAfterVm, (int)nBeforeVm);
    compare("memory rss", (int)nAfterRss, (int)nBeforeRss);
}

// ---------------------------------------------------------------------

bool UnitTestMemoryLeaks::doAfterTest() {
    // do somethig after test
    return true;
}


