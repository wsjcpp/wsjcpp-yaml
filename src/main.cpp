#include <string.h>
#include <iostream>
#include <algorithm>
#include "wsjcpp_yaml.h"
#include "fallen.h"

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    std::string appLogPath = ".wsjcpp-yaml-logs";
    Log::setLogDirectory(appLogPath);
    if (!Fallen::dirExists(appLogPath)) {
        Fallen::makeDir(appLogPath);
    }

    // TODO load and check yaml format

    return 0;
}