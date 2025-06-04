#include <iostream>
#include <wsjcpp_yaml.h>

int main() {
    // https://github.com/wsjcpp/wsjcpp-yaml/issues/29

    std::string sInput =
        "# commet1:\n"
        "\n"
        "val1: 1\n"
        "\n"
        "unit-tests:\n"
        "  cases:\n"
        "    - name: \"NormalizeUnitTestName\"\n"
        "      description: \"Test Normalize UnitTest Name\"\n"
        "    - name: \"generateFilenameForUnitTest\"\n"
        "      description: \"Test generate filename for UnitTest\"\n"
        "    - name: \"InitPackage\"\n"
        "      description: \"Test for init package\"\n"
        "      enabled: \"no\"\n"
        "\n"
        "    - name: \"ReadPackage\"\n"
        "      description: \"Test for read package\"\n"
        "\n"
        "\n"
        "resources:\n"
        "  - filepath: \"./build_simple.sh\"\n"
        "    filesize: 77\n"
        "    pack-as: \"binary\"\n"
        "    modified: 1600401759\n"
        "    sha1: \"\"\n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("input.yml", sInput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    std::string sOutput = "";
    if (!yaml.saveToString(sOutput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    if (sOutput != sInput) {
        std::cerr << "sOutput != sInput" << std::endl;
        return -1;
    }

    // try again

    if (!yaml.loadFromString("output.yml", sOutput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    sOutput = "";
    if (!yaml.saveToString(sOutput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    if (sOutput != sInput) {
        std::cerr << "sOutput != sInput (2)" << std::endl;
        return -1;
    }
    return 0;
}