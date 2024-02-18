#include <string>

#include <gtest/gtest.h>

#include <wsjcpp_yaml.h>

namespace wsjcpp {
namespace yaml {
namespace {

struct WsjcppYamlLineParserTestParams {
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

class WsjcppYamlLineParserParamTest : public ::testing::TestWithParam<WsjcppYamlLineParserTestParams> {};

TEST_P(WsjcppYamlLineParserParamTest, WsjcppYamlLineParserTest) {
  const auto params = GetParam();
  WsjcppYamlParsebleLine line{params.nNumberOfTest};

  std::string error;
  ASSERT_TRUE(line.parseLine(params.sLine, error));

  EXPECT_EQ(line.getPrefix(), params.sPrefix);
  EXPECT_EQ(line.isArrayItem(), params.isArrayItem);
  EXPECT_EQ(line.getName(), params.sName);
  EXPECT_EQ(line.getNameQuotes(), params.nNameQuotes);
  EXPECT_EQ(line.getValue(), params.sValue);
  EXPECT_EQ(line.getValueQuotes(), params.nValueQuotes);
  EXPECT_EQ(line.getComment(), params.sComment);
}

static const std::vector<WsjcppYamlLineParserTestParams> test_cases{
    {
        1, "# Some comment 1 ", "",
        false,                       // array node
        "", WSJCPP_YAML_QUOTES_NONE, // name
        "", WSJCPP_YAML_QUOTES_NONE, // value
        "Some comment 1"             // comment
    },
    {
        2, "  test2: \"t\\\"wo\" # some comment 2  ", "  ",
        false,                              // array node
        "test2", WSJCPP_YAML_QUOTES_NONE,   // name
        "t\"wo", WSJCPP_YAML_QUOTES_DOUBLE, // value
        "some comment 2"                    // comment
    },
    {
        3, "  test3:", "  ",
        false,                            // array node
        "test3", WSJCPP_YAML_QUOTES_NONE, // name
        "", WSJCPP_YAML_QUOTES_NONE,      // value
        ""                                // comment
    },
    {
        4, "  - test4", "  ",
        true,                             // array node
        "", WSJCPP_YAML_QUOTES_NONE,      // name
        "test4", WSJCPP_YAML_QUOTES_NONE, // value
        ""                                // comment
    },
    {
        5, "", "",
        false,                       // array node
        "", WSJCPP_YAML_QUOTES_NONE, // name
        "", WSJCPP_YAML_QUOTES_NONE, // value
        ""                           // comment
    },
    {
        6, "  - \"test4:111\"", "  ",
        true,                                   // array node
        "", WSJCPP_YAML_QUOTES_NONE,            // name
        "test4:111", WSJCPP_YAML_QUOTES_DOUBLE, // value
        ""                                      // comment
    },
    {
        7, "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues", "",
        false,                                                                   // array node
        "issues", WSJCPP_YAML_QUOTES_NONE,                                       // name
        "https://github.com/wsjcpp/wsjcpp-yaml/issues", WSJCPP_YAML_QUOTES_NONE, // value
        ""                                                                       // comment
    }};

INSTANTIATE_TEST_SUITE_P(WsjcppYamlLineParserTest, WsjcppYamlLineParserParamTest, testing::ValuesIn(test_cases));

} // namespace
} // namespace yaml
} // namespace wsjcpp