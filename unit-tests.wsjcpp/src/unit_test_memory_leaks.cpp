#include "get_current_rss.h"
#include "process_mem_usage.h"
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

namespace wsjcpp {
namespace yaml {
namespace {

// ---------------------------------------------------------------------
// UnitTestMemoryLeaks

class UnitTestMemoryLeaks : public WsjcppUnitTestBase {
public:
  UnitTestMemoryLeaks();
  virtual bool doBeforeTest() override;
  virtual void executeTest() override;
  virtual bool doAfterTest() override;

private:
  void createManyTimesObjects();
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestMemoryLeaks)

UnitTestMemoryLeaks::UnitTestMemoryLeaks() : WsjcppUnitTestBase("UnitTestMemoryLeaks") {}

// ---------------------------------------------------------------------

bool UnitTestMemoryLeaks::doBeforeTest() {
  // do something before test
  return true;
}

// ---------------------------------------------------------------------

void UnitTestMemoryLeaks::createManyTimesObjects() {
  std::string sFilepath = "./data-tests/for-memory-leak/some.yml";
  std::string sError;
  for (int i = 0; i < 10000; i++) {
    WsjcppYaml yaml;
    if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
      WsjcppLog::err(TAG, sError);
      return;
    }
  }
}

// ---------------------------------------------------------------------

void UnitTestMemoryLeaks::executeTest() {
  double nBeforeVm, nBeforeRss;
  double nAfterVm, nAfterRss;
  std::string sFilepath = "./data-tests/for-memory-leak/some.yml";

  // first use for memory alloc memory for work
  createManyTimesObjects();

  process_mem_usage(nBeforeVm, nBeforeRss);
  compare("memory vm not null", (int)nBeforeVm > 0, true);
  compare("memory vm not null", (int)nBeforeRss > 0, true);

  // code again check the memoty leak
  createManyTimesObjects();

  process_mem_usage(nAfterVm, nAfterRss);
  compare("memory vm", (int)nAfterVm, (int)nBeforeVm);
  compare("memory rss", (int)nAfterRss, (int)nBeforeRss);
}

// ---------------------------------------------------------------------

bool UnitTestMemoryLeaks::doAfterTest() {
  // do somethig after test
  return true;
}

} // namespace
} // namespace yaml
} // namespace wsjcpp