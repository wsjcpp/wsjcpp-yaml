#include <string.h>
#include <iostream>
#include <algorithm>
#include "wsjcpp_yaml.h"
#include "wsjcpp_core.h"

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    WSJCppCore::initRandom();
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    std::string appLogPath = ".wsjcpp-yaml-logs";
    WSJCppLog::setLogDirectory(appLogPath);
    if (!WSJCppCore::dirExists(appLogPath)) {
        WSJCppCore::makeDir(appLogPath);
    }

    // TODO load and check yaml format

    return 0;
}