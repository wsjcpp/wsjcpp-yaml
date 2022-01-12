#include <string.h>
#include <iostream>
#include <algorithm>
#include "examples.h"
#include "wsjcpp_yaml.h"

// #include "wsjcpp_core.h"

class MyLogger : public IWsjcppYamlLog {
    public:
        // IWsjcppYamlLog
        virtual void err(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [error] : " << sMessage << std::endl;
        };
        virtual void throw_err(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [critical_error] : " << sMessage << std::endl;
            throw std::runtime_error(TAG + " [critical_error] : " + sMessage);
        };
        virtual void warn(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [warn] : " << sMessage << std::endl;
        };
        virtual void info(const std::string &TAG, const std::string &sMessage) override {
            std::cout << TAG << " [info] : " << sMessage << std::endl;
        };
};

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    // WsjcppCore::initRandom();
    // std::string appName = std::string(WSJCPP_APP_NAME);
    // std::string appVersion = std::string(WSJCPP_APP_VERSION);
    // std::string appLogPath = ".wsjcpp-yaml-logs";
    // WsjcppLog::setLogDirectory(appLogPath);
    // if (!WsjcppCore::dirExists(appLogPath)) {
    //     WsjcppCore::makeDir(appLogPath);
    // }
    MyLogger *pLogger = new MyLogger();

    WsjcppYaml yaml;
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
        std::cerr << "Could not save data to file: " << sFilePath.c_str() << std::endl << "Error: " << sError.c_str() << std::endl;
        // WsjcppLog::err(TAG, );
        return -1;
    }
    std::cout << "Done." << std::endl;
    std::string s = yaml["version"];
    // int nVer = yaml["version"];
    // bool bVer = yaml["version"];
    std::cout << s << std::endl;

    example_operator_1();
    return 0;
}
