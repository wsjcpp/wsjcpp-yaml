#include <iostream>
#include <wsjcpp_yaml.h>

int main() {
    std::string sTestYaml1 =
        "# Some comment 1\n"
        "test10: one\n"
        "test20: two # some comment 2\n"
    ;

    std::string sTestYaml2 =
        "# Some comment 1\n"
        "test11: one\n"
        "test20: two # some comment 2\n"
        "test22: two # some comment 2\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    int ret = 0;

    if (!yaml.loadFromString("parse1", sTestYaml1, sError)) {
        std::cerr << "Error parsing 1 " << sError << std::endl;
        return -1;
    }

    if (!yaml.getRoot()->hasElement("test10")) {
        std::cerr << "Failed check '(1) has test10'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->hasElement("test11")) {
        std::cerr << "Failed check '(1) has test11'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("test20")) {
        std::cerr << "Failed check '(1) has test20'" << std::endl;
        ret = -1;
    }

    if (yaml.getRoot()->hasElement("test22")) {
        std::cerr << "Failed check '(1) has test22'" << std::endl;
        ret = -1;
    }

    // 2

    if (!yaml.loadFromString("parse2", sTestYaml2, sError)) {
        std::cerr << "Error parsing 2 " << sError << std::endl;
        return -1;
    }

    if (yaml.getRoot()->hasElement("test10")) {
        std::cerr << "Failed check '(2) has test10'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("test11")) {
        std::cerr << "Failed check '(2) has test11'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("test20")) {
        std::cerr << "Failed check '(2) has test20'" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("test22")) {
        std::cerr << "Failed check '(2) has test22'" << std::endl;
        ret = -1;
    }

    // 3

    yaml.clear();

    if (yaml.getRoot() != nullptr) {
        std::cerr << "Failed check '(3) has root'" << std::endl;
        ret = -1;
    }

    return ret;
}