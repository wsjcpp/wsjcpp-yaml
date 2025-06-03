#include <vector>
#include <iostream>
#include <cmath>
#include <wsjcpp_yaml.h>

int main() {
    WsjcppYaml yaml;
    std::string sFilepath = "../../../../src/tests/data-tests/python_yaml_issue_33/example.yaml";
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;

    if (!yaml.getRoot()->hasElement("2021-10-08")) {
        std::cerr << "Element '2021-10-08' not found" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("2021-10-11")) {
        std::cerr << "Element '2021-10-08' not found" << std::endl;
        ret = -1;
    }

    // TODO
    return -1;
}