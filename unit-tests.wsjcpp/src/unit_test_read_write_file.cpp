
#include <wsjcpp_core.h>
#include <wsjcpp_unit_tests.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestReadWriteFile

class UnitTestReadWriteFile : public WsjcppUnitTestBase {
    public:
        UnitTestReadWriteFile();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestReadWriteFile)

UnitTestReadWriteFile::UnitTestReadWriteFile()
    : WsjcppUnitTestBase("UnitTestReadWriteFile") {
}

// ---------------------------------------------------------------------

bool UnitTestReadWriteFile::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestReadWriteFile::executeTest() {
    WsjcppYaml yaml;
    std::string sFilepath = "./data-tests/read-write-file/docker-compose.yml";
    std::string sFilepathOutput = "./data-tests/read-write-file/docker-compose.output.yml";
    std::string sError;
    if (!compare("Error parsing", yaml.loadFromFile(sFilepath, sError), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    compare("has version", yaml.getRoot()->hasElement("version"), true);
    compare("has volumes", yaml.getRoot()->hasElement("volumes"), true);
    compare("has networks", yaml.getRoot()->hasElement("networks"), true);
    compare("has services", yaml.getRoot()->hasElement("services"), true);

    compare("version-value", yaml.getRoot()->getElement("version")->getStringValue(), "3");
    compare("version-value", yaml.getRoot()->getElement("version")->getIntValue(), 3); // wrong or not ?

    if (!compare("Error parsing", yaml.saveToFile(sFilepathOutput), true)) {
        WsjcppLog::err(TAG, sError);
        return;
    }

    std::string sOriginalFileContent;
    WsjcppCore::readTextFile(sFilepath, sOriginalFileContent);
    std::string sOutputFileContent;
    WsjcppCore::readTextFile(sFilepathOutput, sOutputFileContent);

    compare("compare conteent ", sOutputFileContent, sOriginalFileContent);

}

// ---------------------------------------------------------------------

bool UnitTestReadWriteFile::doAfterTest() {
    // do somethig after test
    return true;
}


