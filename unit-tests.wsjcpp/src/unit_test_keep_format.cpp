
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestKeepFormat

class UnitTestKeepFormat : public WsjcppUnitTestBase {
    public:
        UnitTestKeepFormat();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestKeepFormat)

UnitTestKeepFormat::UnitTestKeepFormat()
    : WsjcppUnitTestBase("UnitTestKeepFormat") {
}

// ---------------------------------------------------------------------

bool UnitTestKeepFormat::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestKeepFormat::executeTest() {
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
    if (!compare("Error parsing", yaml.loadFromString("input.yml", sInput, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    std::string sOutput = "";
    if (!compare("Error parsing", yaml.saveToString(sOutput, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    if (!compare("Keep formating", sOutput, sInput)) {
        return;
    }

    // try again
    if (!compare("Error parsing", yaml.loadFromString("output.yml", sOutput, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    sOutput = "";
    if (!compare("Error parsing", yaml.saveToString(sOutput, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    if (!compare("Keep formating", sOutput, sInput)) {
        return;
    }
}

// ---------------------------------------------------------------------

bool UnitTestKeepFormat::doAfterTest() {
    // do somethig after test
    return true;
}


