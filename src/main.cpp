#include <string.h>
#include <iostream>
#include <algorithm>
#include "wsjcpp_yaml.h"
// #include "wsjcpp_core.h"

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
    WsjcppYaml yaml;
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
    

    return 0;
}
