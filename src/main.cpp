#include <string.h>
#include <iostream>
#include <algorithm>
#include "wsjcpp_yaml.h"
#include "wsjcpp_core.h"

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    WsjcppCore::initRandom();
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    std::string appLogPath = ".wsjcpp-yaml-logs";
    WsjcppLog::setLogDirectory(appLogPath);
    if (!WsjcppCore::dirExists(appLogPath)) {
        WsjcppCore::makeDir(appLogPath);
    }
    WsjcppYaml yaml;
    if (!yaml.loadFromFile("./wsjcpp.yml")) {
        WsjcppLog::err(TAG, "Could not read data from file");
        return -1;
    }
    
    if (!yaml.saveToFile("./wsjcpp.yml")) {
        WsjcppLog::err(TAG, "Could not save data to file");
        return -1;
    }

    return 0;
}
