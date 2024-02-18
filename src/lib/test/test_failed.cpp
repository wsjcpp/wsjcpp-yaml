#include <string_view>
#include <string>
#include <gtest/gtest.h>
#include <wsjcpp_yaml.h>

namespace {

TEST(WsjcppYamlTest, Failed) {
  static const std::string sTestYaml1 = "(# Some comment 1\n"
    "test10: one\n"
    "test20: two # some comment 2)\n";

  WsjcppYaml yaml;
  std::string sError;

  ASSERT_FALSE(yaml.loadFromString("parse1", std::string{sTestYaml1}, sError));

  EXPECT_EQ(yaml.getRoot()->toString(), "");
}

} // namespace