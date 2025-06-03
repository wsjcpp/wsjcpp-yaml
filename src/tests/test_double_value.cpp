#include <vector>
#include <iostream>
#include <cmath>
#include <wsjcpp_yaml.h>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

int main() {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX );
    std::cout << "Current path: " << buff << std::endl;

    WsjcppYaml yaml;
    std::string sFilepath = "../../../../src/tests/data-tests/float-double/example.yml";
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;
    if (!yaml.getRoot()->hasElement("double")) {
        std::cerr << "Parameter 'float' not found" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("double")) {
        std::cerr << "Parameter 'double' has not value" << std::endl;
        ret = -1;
    }

    std::string expected_val_str = "1.0002";
    if (yaml.getRoot()->getElement("double")->getValue() != expected_val_str) {
        std::cerr << "Parameter 'double' has value string '" << yaml.getRoot()->getElement("double")->getValue() << "', but expected '" << expected_val_str << "'" << std::endl;
        ret = -1;
    }

    double val_double = yaml["double"].valDouble();
    double expected_double = 1.0002f;
    // std::numeric_limits<double>::epsilon() => 2.22045e-16
    // std::numeric_limits<float>::epsilon() => 1.19209e-07
    // abs(val_double - expected_double) => 3.31879e-08
    if (abs(val_double - expected_double) > std::numeric_limits<float>::epsilon()) {
        std::cerr << "Parameter 'double' has value number '" << val_double << "', but expected '" << expected_double << "'" << std::endl;
        ret = -1;
    }

    yaml["double"].val(1.0003f);

    expected_val_str = "1.0003";
    if (yaml.getRoot()->getElement("double")->getValue() != expected_val_str) {
        std::cerr << "Parameter 'double' has value string '" << yaml.getRoot()->getElement("double")->getValue() << "', but expected '" << expected_val_str << "'" << std::endl;
        ret = -1;
    }

    expected_double = 1.0003f;
    val_double = yaml["double"].valDouble();
    if (abs(val_double - expected_double) > std::numeric_limits<float>::epsilon()) {
        std::cerr << "Parameter 'double' has value number '" << val_double << "', but expected '" << expected_double << "'" << std::endl;
        ret = -1;
    }
    float val_double_like_float = yaml["double"].valFloat();
    float expected_float = 1.0003f;
    if (abs(val_double_like_float - expected_float) > std::numeric_limits<float>::epsilon()) {
        std::cerr << "Parameter 'double' has value number (like float) '" << val_double_like_float << "', but expected '" << expected_float << "'" << std::endl;
        ret = -1;
    }

    // compareD("has double value is 1.0003 (double 2)", yaml["double"].valDouble(), 1.0003f);

    return ret;
}