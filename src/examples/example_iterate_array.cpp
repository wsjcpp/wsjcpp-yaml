#include "examples.h"

#include "wsjcpp_yaml.h"

void example_iterate_array() {

    std::string sTest =     
        "'2021-10-08':\n"
        "  - code: '300209'\n"
        "    focusstr: ''\n"
        "  - code: '300047'\n"
        "    focusstr: ''\n"
        "  - code: '300970'\n"
        "    focusstr: ''\n"
        "  - code: '300288'\n"
        "    focusstr: ''\n"
        "'2021-10-11':\n"
        "  - code: '300162'\n"
        "    focusstr: ''\n"
        "  - code: '300209'\n"
        "    focusstr: ''\n"
        "  - code: '300972'\n"
        "    focusstr: ''\n"
        "  - code: '300159'\n"
        "    focusstr: ''\n"
    ;

    WsjcppYaml yaml2;
    std::string sError;
    if (!yaml2.loadFromString("test", sTest, sError)) {
        std::cerr << sError << std::endl;
        return;
    }
    WsjcppYamlCursor cur = yaml2.getCursor();
    std::vector<std::string> vKeys = cur.keys();
    for (int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        int nCount = cur[sKey].size(); // musts array
        for (int n = 0; n < nCount; n++) {
            WsjcppYamlCursor el = cur[sKey][n];
            std::cout
                << "code = " << el["code"].valInt()
                << "; focusstr = " << el["focusstr"].valStr()
                << ";"
                << std::endl;
        }
    }
}