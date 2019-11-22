#include <string.h>
#include <iostream>
#include <algorithm>
#include "wsjcpp_yaml.h"
#include "fallen.h"

int g_nErrors = 0;
std::string g_sTestYaml = 
    "# Some comment 1\n"
    "test10: one\n"
    "test20: two # some comment 2\n"
    "\n" // empty line
    "array30:\n"
    "  - one31 # this field for test array30 \n"
    "  - two32\n"
    "  - three33\n"
    "\n" // empty line
    "array40: # some comment 3\n"
    "  - \"one#1\" # some comment\n"
    "  # some comment\n"
    "  - \"two#2\"\n"
    "array50: # some comment 3\n"
    "  - p1: test501\n"
    "    p2: test502\n"
    "  - p1: test503\n"
    "    p2: test504\n"
    "\n" // empty line
    "map60: # some comment 4\n"
    "  test70: opa1\n"
    "  test80: opa2\n"
;

void check(std::string sTestName, std::string sGotValue, std::string sExpectedValue) {
    if (sGotValue != sExpectedValue) {
        Log::err(sTestName, "Expected value: '" + sExpectedValue + "', but got: '" + sGotValue + "'");
        g_nErrors++;
        return;
    }
    Log::ok(sTestName, "fine");
};

void check(std::string sTestName, bool bGotValue, bool bExpectedValue) {
    std::string sGotValue = bGotValue ? "yes" : "no";
    std::string sExpectedValue = bExpectedValue ? "yes" : "no";
    if (sGotValue != sExpectedValue) {
        Log::err(sTestName, "Expected value: '" + sExpectedValue + "', but got: '" + sGotValue + "'");
        g_nErrors++;
        return;
    }
    Log::ok(sTestName, "fine");
};

void testLine(
    int nNumberOfTest, 
    std::string sLine,
    std::string sPrefix,
    bool isArrayItem,
    std::string sName,
    std::string sValue,
    std::string sComment
) {
    std::string TAG = "LINE" + std::to_string(nNumberOfTest);
    WSJCppYAMLParsebleLine line(nNumberOfTest);
    Log::info(TAG, "Test line" + std::to_string(nNumberOfTest) + ": '" + sLine + "'");
    line.parseLine(sLine);
    check(TAG + "-prefix", line.getPrefix(), sPrefix);
    check(TAG + "-arrayitem", line.isArrayItem(), isArrayItem);
    check(TAG + "-name", line.getName(), sName);
    check(TAG + "-value", line.getValue(), sValue);
    check(TAG + "-comment", line.getComment(), sComment);
};

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    std::string appLogPath = ".wsjcpp-yaml-logs";
    Log::setLogDirectory(appLogPath);
    if (!Fallen::dirExists(appLogPath)) {
        Fallen::makeDir(appLogPath);
    }

    // tests for line parser
    testLine(1, "# Some comment 1 ", "", false, "", "", " Some comment 1 ");
    testLine(2, "  test2: \"t\\\"wo\" # some comment 2", "  ", false, "test2", "t\"wo", " some comment 2");
    testLine(3, "  test3:", "  ", false, "test3", "", "");
    testLine(4, "  - test4", "  ", true, "", "test4", "");
    testLine(5, "", "", false, "", "", "");

    // tests
    

    WSJCppYAML yaml;
    if (yaml.loadFromString(g_sTestYaml)) {
        Log::throw_err(TAG, "Error parsing");
        return -1;
    }
    std::string sSaved = "";
    if (yaml.saveToString(sSaved)) {
        Log::info(TAG, "\n>>>>\n" + sSaved);
    }
    
    WSJCppYAMLItem *pItem = nullptr;
    check("test10", yaml.getRoot()->getElement("test10")->getValue(), "one");
    check("test20", yaml.getRoot()->getElement("test20")->getValue(), "two");
    
    pItem = yaml.getRoot()->getElement("array30");
    check("array30_length", pItem->getLength(), 3);
    pItem = yaml.getRoot()->getElement("array30")->getElement(0);
    check("test30_value", pItem->getValue(), "one31");
    check("test30_comment", pItem->getComment(), " this field for test array30 ");
    pItem = yaml.getRoot()->getElement("array30")->getElement(1);
    check("test40_value", pItem->getValue(), "two32");
    check("test40_comment", pItem->getComment(), "");

    pItem = yaml.getRoot()->getElement("array40");
    check("array40_length", pItem->getLength(), 2);

    pItem = yaml.getRoot()->getElement("array50");
    check("array50_length", pItem->getLength(), 1);
    
    pItem = yaml.getRoot()->getElement("map60")->getElement("test70");
    check("test70_value", pItem->getValue(), "opa1");

    pItem = yaml.getRoot()->getElement("map60")->getElement("test80");
    check("test80_comment", pItem->getValue(), "opa2");

    std::string sTestExpectedYaml = 
        "# Some comment 1\n"
        "test: one\n"
        "test2: two # some comment 2\n"
        "\n" // empty line
        "array:\n"
        "  - one\n"
        "  - two\n"
        "\n" // empty line
        "array2: # some comment 3\n"
        "  - \"one#1\"\n"
        "  - \"two#2\"\n"
        "\n" // empty line
        "map: # some comment 4\n"
        "  test3: 1\n"
        "  test4: 2\n"
        "\n" // empty line
    ;

    sSaved = "";
    if (yaml.saveToString(sSaved)) {
        check("yaml_save", sSaved, sTestExpectedYaml);
    }

    return 0;
}