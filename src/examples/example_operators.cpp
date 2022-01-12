#include "examples.h"

#include "wsjcpp_yaml.h"

void example_operator_1() {

    std::string sTest =     
        "test: 'string'\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("test", sTest, sError)) {
        std::cerr << sError << std::endl;
        return;
    }
    WsjcppYamlCursor cur = yaml.getCursor();
    std::cout << "before : " << cur["test"].valStr() << std::endl;
    cur["test"] = "some new string";
    std::cout << "after 1 : " << cur["test"].valStr() << std::endl;
    cur["test"] = 111;
    std::cout << "after 2 : " << cur["test"].valStr() << std::endl;
    cur["test"] = true;
    std::cout << "after 3 : " << cur["test"].valStr() << std::endl;
}