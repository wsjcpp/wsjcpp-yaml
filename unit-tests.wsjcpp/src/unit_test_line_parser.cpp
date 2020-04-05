#include "unit_test_line_parser.h"
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestLineParser)

UnitTestLineParser::UnitTestLineParser()
    : WsjcppUnitTestBase("UnitTestLineParser") {
    //
}

// ---------------------------------------------------------------------

void UnitTestLineParser::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestLineParser::run() {
    struct LineTest {
        LineTest(
            int nNumberOfTest,
            std::string sLine,
            std::string sPrefix,
            bool isArrayItem,
            std::string sName,
            bool bNameHasQuotes,
            std::string sValue,
            bool bValueHasQuotes,
            std::string sComment
        ) : nNumberOfTest(nNumberOfTest),
            sLine(sLine),
            sPrefix(sPrefix),
            isArrayItem(isArrayItem),
            sName(sName),
            bNameHasQuotes(bNameHasQuotes),
            sValue(sValue),
            bValueHasQuotes(bValueHasQuotes),
            sComment(sComment)
        {
            //    
        };
        int nNumberOfTest;
        std::string sLine;
        std::string sPrefix;
        bool isArrayItem;
        std::string sName;
        bool bNameHasQuotes;
        std::string sValue;
        bool bValueHasQuotes;
        std::string sComment;
    };

    std::vector<LineTest> vTestLines;

    vTestLines.push_back(LineTest(1, "# Some comment 1 ", "", false, "", false, "", false, "Some comment 1"));
    vTestLines.push_back(LineTest(2, "  test2: \"t\\\"wo\" # some comment 2  ", "  ", false, "test2", false, "t\"wo", true, "some comment 2"));
    vTestLines.push_back(LineTest(3, "  test3:", "  ", false, "test3", false,  "", false,  ""));
    vTestLines.push_back(LineTest(4, "  - test4", "  ", true, "", false,  "test4", false, ""));
    vTestLines.push_back(LineTest(5, "", "", false, "", false,  "", false,  ""));
    vTestLines.push_back(LineTest(6, "  - \"test4:111\"", "  ", true, "", false,  "test4:111", true, ""));
    vTestLines.push_back(LineTest(7, "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues", "", false, "issues", false,  "https://github.com/wsjcpp/wsjcpp-yaml/issues", false, ""));

    bool bTestSuccess = true;

    for (int i = 0; i < vTestLines.size(); i++) {
        LineTest test = vTestLines[i];
        
        WsjcppYamlParsebleLine line(test.nNumberOfTest);
        line.parseLine(test.sLine);

        std::string tagline = "{line:" + std::to_string(test.nNumberOfTest) + ": '" + test.sLine + "'}";
        compareS(bTestSuccess, tagline + ", prefix", line.getPrefix(), test.sPrefix);
        compareB(bTestSuccess, tagline + ", arrayitem", line.isArrayItem(), test.isArrayItem);
        compareS(bTestSuccess, tagline + ", name", line.getName(), test.sName);
        compareB(bTestSuccess, tagline + ", name-has-quotes", line.hasNameDoubleQuotes(), test.bNameHasQuotes);
        compareS(bTestSuccess, tagline + ", value", line.getValue(), test.sValue);
        compareB(bTestSuccess, tagline + ", value-has-quotes", line.hasValueDoubleQuotes(), test.bValueHasQuotes);
        compareS(bTestSuccess, tagline + ", comment", line.getComment(), test.sComment);
    }

    return bTestSuccess;
}