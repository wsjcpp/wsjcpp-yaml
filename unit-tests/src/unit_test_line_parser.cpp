#include "unit_test_line_parser.h"
#include <vector>
#include <iostream>
#include <fallen.h>
#include <wsjcpp_yaml.h>

REGISTRY_UNIT_TEST(UnitTestLineParser)

UnitTestLineParser::UnitTestLineParser()
    : UnitTestBase("UnitTestLineParser") {
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
            std::string sValue,
            std::string sComment
        ) : nNumberOfTest(nNumberOfTest),
            sLine(sLine),
            sPrefix(sPrefix),
            isArrayItem(isArrayItem),
            sName(sName),
            sValue(sValue),
            sComment(sComment)
        {
            //    
        };
        int nNumberOfTest;
        std::string sLine;
        std::string sPrefix;
        bool isArrayItem;
        std::string sName;
        std::string sValue;
        std::string sComment;
    };

    std::vector<LineTest> vTestLines;

    vTestLines.push_back(LineTest(1, "# Some comment 1 ", "", false, "", "", "Some comment 1"));
    vTestLines.push_back(LineTest(2, "  test2: \"t\\\"wo\" # some comment 2  ", "  ", false, "test2", "t\"wo", "some comment 2"));
    vTestLines.push_back(LineTest(3, "  test3:", "  ", false, "test3", "", ""));
    vTestLines.push_back(LineTest(4, "  - test4", "  ", true, "", "test4", ""));
    vTestLines.push_back(LineTest(5, "", "", false, "", "", ""));

    bool bTestSuccess = true;

    for (int i = 0; i < vTestLines.size(); i++) {
        LineTest test = vTestLines[i];
        
        WSJCppYAMLParsebleLine line(test.nNumberOfTest);
        line.parseLine(test.sLine);

        std::string tagline = "{line:" + std::to_string(test.nNumberOfTest) + ": '" + test.sLine + "'}";
        compareS(bTestSuccess, tagline + ", prefix", line.getPrefix(), test.sPrefix);
        compareB(bTestSuccess, tagline + ", arrayitem", line.isArrayItem(), test.isArrayItem);
        compareS(bTestSuccess, tagline + ", name", line.getName(), test.sName);
        compareS(bTestSuccess, tagline + ", value", line.getValue(), test.sValue);
        compareS(bTestSuccess, tagline + ", comment", line.getComment(), test.sComment);
    }

    return bTestSuccess;
}