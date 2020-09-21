#include <wsjcpp_unit_tests.h>
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// UnitTestLineParser

class UnitTestLineParser : public WsjcppUnitTestBase {
    public:
        UnitTestLineParser();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestLineParser)

UnitTestLineParser::UnitTestLineParser()
    : WsjcppUnitTestBase("UnitTestLineParser") {
    //
}

// ---------------------------------------------------------------------

bool UnitTestLineParser::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestLineParser::executeTest() {
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

    for (int i = 0; i < vTestLines.size(); i++) {
        LineTest test = vTestLines[i];
        std::string tagline = "{line:" + std::to_string(test.nNumberOfTest) + ": '" + test.sLine + "'}";

        WsjcppYamlParsebleLine line(test.nNumberOfTest);
        std::string sError;
        if (!compare(tagline + ", parseLine", line.parseLine(test.sLine, sError), true)) {
            WsjcppLog::err(tagline + ", parseLine", sError);
            return;
        }

        compare(tagline + ", prefix", line.getPrefix(), test.sPrefix);
        compare(tagline + ", arrayitem", line.isArrayItem(), test.isArrayItem);
        compare(tagline + ", name", line.getName(), test.sName);
        compare(tagline + ", name-has-quotes", line.hasNameDoubleQuotes(), test.bNameHasQuotes);
        compare(tagline + ", value", line.getValue(), test.sValue);
        compare(tagline + ", value-has-quotes", line.hasValueDoubleQuotes(), test.bValueHasQuotes);
        compare(tagline + ", comment", line.getComment(), test.sComment);
    }
}

// ---------------------------------------------------------------------

bool UnitTestLineParser::doAfterTest() {
    // do somethig after test
    return true;
}