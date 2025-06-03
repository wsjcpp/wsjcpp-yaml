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
    GetCurrentDir(buff, FILENAME_MAX);
    std::cout << "Current path: " << buff << std::endl;

    WsjcppYaml yaml;
    std::string sFilepath = "../../../../src/tests/data-tests/float-double/example.yml";
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;
    if (!yaml.getRoot()->hasElement("float")) {
        std::cerr << "Parameter 'float' not found" << std::endl;
        ret = -1;
    }

    if (!yaml.getRoot()->hasElement("float")) {
        std::cerr << "Parameter 'float' has not value" << std::endl;
        ret = -1;
    }

    std::string value_float = yaml["float"];

    std::string expected_val_str = "1.0001";
    if (value_float != expected_val_str) {
        std::cerr << "Parameter 'float' has value '" << value_float << "', but expected '" << expected_val_str << "'" << std::endl;
        ret = -1;
    }

    float val_float = yaml["float"].valFloat();
    float expected_float = 1.0001f;
    if (abs(val_float - expected_float) > std::numeric_limits<float>::epsilon()) {
        std::cerr << "Parameter 'float' has value '" << val_float << "', but expected '" << expected_float << "'" << std::endl;
        ret = -1;
    }

    return ret;
}