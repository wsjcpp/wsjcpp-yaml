#include <wsjcpp_unit_tests.h>
#include <vector>
#include <iostream>
#include <wsjcpp_yaml.h>

namespace wsjcpp {
namespace yaml {
namespace {

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

UnitTestLineParser::UnitTestLineParser() : WsjcppUnitTestBase("UnitTestLineParser") {
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
    LineTest(int nNumberOfTest, std::string sLine, std::string sPrefix, bool isArrayItem, std::string sName,
             WsjcppYamlQuotes nNameQuotes, std::string sValue, WsjcppYamlQuotes nValueQuotes, std::string sComment)
        : nNumberOfTest(nNumberOfTest), sLine(sLine), sPrefix(sPrefix), isArrayItem(isArrayItem), sName(sName),
          nNameQuotes(nNameQuotes), sValue(sValue), nValueQuotes(nValueQuotes), sComment(sComment){
                                                                                    //
                                                                                };
    int nNumberOfTest;
    std::string sLine;
    std::string sPrefix;
    bool isArrayItem;
    std::string sName;
    WsjcppYamlQuotes nNameQuotes;
    std::string sValue;
    WsjcppYamlQuotes nValueQuotes;
    std::string sComment;
  };

  std::vector<LineTest> vTestLines;

  vTestLines.push_back(LineTest(1, "# Some comment 1 ", "",
                                false,                       // array node
                                "", WSJCPP_YAML_QUOTES_NONE, // name
                                "", WSJCPP_YAML_QUOTES_NONE, // value
                                "Some comment 1"             // comment
                                ));
  vTestLines.push_back(LineTest(2, "  test2: \"t\\\"wo\" # some comment 2  ", "  ",
                                false,                              // array node
                                "test2", WSJCPP_YAML_QUOTES_NONE,   // name
                                "t\"wo", WSJCPP_YAML_QUOTES_DOUBLE, // value
                                "some comment 2"                    // comment
                                ));
  vTestLines.push_back(LineTest(3, "  test3:", "  ",
                                false,                            // array node
                                "test3", WSJCPP_YAML_QUOTES_NONE, // name
                                "", WSJCPP_YAML_QUOTES_NONE,      // value
                                ""                                // comment
                                ));
  vTestLines.push_back(LineTest(4, "  - test4", "  ",
                                true,                             // array node
                                "", WSJCPP_YAML_QUOTES_NONE,      // name
                                "test4", WSJCPP_YAML_QUOTES_NONE, // value
                                ""                                // comment
                                ));
  vTestLines.push_back(LineTest(5, "", "",
                                false,                       // array node
                                "", WSJCPP_YAML_QUOTES_NONE, // name
                                "", WSJCPP_YAML_QUOTES_NONE, // value
                                ""                           // comment
                                ));
  vTestLines.push_back(LineTest(6, "  - \"test4:111\"", "  ",
                                true,                                   // array node
                                "", WSJCPP_YAML_QUOTES_NONE,            // name
                                "test4:111", WSJCPP_YAML_QUOTES_DOUBLE, // value
                                ""                                      // comment
                                ));
  vTestLines.push_back(LineTest(7, "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues", "",
                                false,                                                                   // array node
                                "issues", WSJCPP_YAML_QUOTES_NONE,                                       // name
                                "https://github.com/wsjcpp/wsjcpp-yaml/issues", WSJCPP_YAML_QUOTES_NONE, // value
                                ""                                                                       // comment
                                ));

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
    compare(tagline + ", name-has-quotes", line.getNameQuotes(), test.nNameQuotes);
    compare(tagline + ", value", line.getValue(), test.sValue);
    compare(tagline + ", value-quotes", line.getValueQuotes(), test.nValueQuotes);
    compare(tagline + ", comment", line.getComment(), test.sComment);
  }
}

// ---------------------------------------------------------------------

bool UnitTestLineParser::doAfterTest() {
  // do somethig after test
  return true;
}

} // namespace
} // namespace yaml
} // namespace wsjcpp