#include <algorithm>
#include <iostream>
#include <sstream>
#include <string.h>

#include <wsjcpp_yaml.h>

#include "examples.h"

namespace wsjcpp {
namespace {

class MyLogger : public yaml::IWsjcppYamlLog {
public:
  // IWsjcppYamlLog
  virtual void err(const std::string &TAG, const std::string &sMessage) override {
    std::cerr << TAG << " [error] : " << sMessage << std::endl;
  };
  virtual void throw_err(const std::string &TAG, const std::string &sMessage) override {
    const auto message = [&]() -> std::string {
      std::ostringstream oss;
      oss << TAG << " [critical_error] : " << sMessage;
      return oss.str();
    }();
    std::cerr << message << std::endl;
    throw std::runtime_error(message);
  };
  virtual void warn(const std::string &TAG, const std::string &sMessage) override {
    std::cerr << TAG << " [warn] : " << sMessage << std::endl;
  };
  virtual void info(const std::string &TAG, const std::string &sMessage) override {
    std::cout << TAG << " [info] : " << sMessage << std::endl;
  };
};

} // namespace
} // namespace wsjcpp

int main(int argc, char *argv[]) {
  std::string TAG = "MAIN";
  // WsjcppCore::initRandom();
  // std::string appName = std::string(WSJCPP_APP_NAME);
  // std::string appVersion = std::string(WSJCPP_APP_VERSION);
  // std::string appLogPath = ".wsjcpp-yaml-logs";
  // WsjcppLog::setLogDirectory(appLogPath);
  // if (!WsjcppCore::dirExists(appLogPath)) {
  //     WsjcppCore::makeDir(appLogPath);
  // }
  auto *pLogger = new wsjcpp::MyLogger();

  wsjcpp::yaml::WsjcppYaml yaml;
  yaml.setLogger(pLogger);
  std::string sError;
  std::string sFilePath = "./unit-tests.wsjcpp/data-tests/read-file/example-voiting-app/docker-compose.yml";
  std::cout << "Reading file " << sFilePath << "..." << std::endl;
  if (!yaml.loadFromFile(sFilePath, sError)) {
    std::cerr << "Error: " << sError.c_str() << std::endl;
    // WsjcppLog::err(TAG, sError);
    return -1;
  }
  std::cout << "Done." << std::endl;

  std::cout << "Saving to file " << sFilePath << "..." << std::endl;
  if (!yaml.saveToFile(sFilePath, sError)) {
    std::cerr << "Could not save data to file: " << sFilePath.c_str() << std::endl
              << "Error: " << sError.c_str() << std::endl;
    // WsjcppLog::err(TAG, );
    return -1;
  }
  std::cout << "Done." << std::endl;
  std::string sVer = yaml["version"];
  int nVer = yaml["version"];
  bool bVer = yaml["version"];
  std::cout << sVer << std::endl;
  std::cout << nVer << std::endl;
  std::cout << bVer << std::endl;

  wsjcpp::yaml::example_operator_1();
  return 0;
}
