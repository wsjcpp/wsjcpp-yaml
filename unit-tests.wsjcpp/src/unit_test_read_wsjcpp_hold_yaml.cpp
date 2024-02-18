
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

namespace wsjcpp {
namespace yaml {
namespace {

// ---------------------------------------------------------------------
// UnitTestReadWsjcppHoldYml

class UnitTestReadWsjcppHoldYml : public WsjcppUnitTestBase {
public:
  UnitTestReadWsjcppHoldYml();
  virtual bool doBeforeTest() override;
  virtual void executeTest() override;
  virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestReadWsjcppHoldYml)

UnitTestReadWsjcppHoldYml::UnitTestReadWsjcppHoldYml() : WsjcppUnitTestBase("UnitTestReadWsjcppHoldYml") {}

// ---------------------------------------------------------------------

bool UnitTestReadWsjcppHoldYml::doBeforeTest() {
  // do something before test
  return true;
}

// ---------------------------------------------------------------------

void UnitTestReadWsjcppHoldYml::executeTest() {
  WsjcppYaml yaml;
  std::string sFilepath = "./data-tests/read-wsjcpp-hold-yml/wsjcpp.hold.yml";
  std::string sError;
  if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
    WsjcppLog::err(TAG, sError);
    return;
  }
}

// ---------------------------------------------------------------------

bool UnitTestReadWsjcppHoldYml::doAfterTest() {
  // do somethig after test
  return true;
}

} // namespace
} // namespace yaml
} // namespace wsjcpp