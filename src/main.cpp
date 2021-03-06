#include <string.h>
#include <iostream>
#include <algorithm>
#include "wsjcpp_yaml.h"
#include "wsjcpp_core.h"

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    WsjcppCore::initRandom();
    std::string appName = std::string(WSJCPP_APP_NAME);
    std::string appVersion = std::string(WSJCPP_APP_VERSION);
    std::string appLogPath = ".wsjcpp-yaml-logs";
    WsjcppLog::setLogDirectory(appLogPath);
    if (!WsjcppCore::dirExists(appLogPath)) {
        WsjcppCore::makeDir(appLogPath);
    }
    WsjcppYaml yaml;
    std::string sError; 
    std::string sFilePath = "./unit-tests.wsjcpp/data-tests/read-file/example-voiting-app/docker-compose.yml";
    if (!yaml.loadFromFile(sFilePath, sError)) {
        WsjcppLog::err(TAG, "Could not read data from file: " + sError);
        return -1;
    }
    
    if (!yaml.saveToFile(sFilePath, sError)) {
        WsjcppLog::err(TAG, "Could not save data to file: " + sError);
        return -1;
    }

    return 0;
}
