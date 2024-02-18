#include <string_view>
#include <string>
#include <gtest/gtest.h>
#include <wsjcpp_yaml.h>

namespace {

TEST(WsjcppYamlTest, Cleanup) {
  static const std::string sTestYaml1 = "# Some comment 1\n"
    "test10: one\n"
    "test20: two # some comment 2\n";

  static const std::string sTestYaml2 = "# Some comment 1\n"
    "test11: one\n"
    "test20: two # some comment 2\n"
    "test22: two # some comment 2";

  WsjcppYaml yaml;
  std::string sError;

  ASSERT_TRUE(yaml.loadFromString("parse1", std::string{sTestYaml1}, sError));

  EXPECT_TRUE(yaml.getRoot()->hasElement("test10"));
  EXPECT_FALSE(yaml.getRoot()->hasElement("test11"));
  EXPECT_TRUE(yaml.getRoot()->hasElement("test20"));
  EXPECT_FALSE(yaml.getRoot()->hasElement("test22"));

  ASSERT_TRUE(yaml.loadFromString("parse2", std::string{sTestYaml2}, sError));

  EXPECT_FALSE(yaml.getRoot()->hasElement("test10"));
  EXPECT_TRUE(yaml.getRoot()->hasElement("test11"));
  EXPECT_TRUE(yaml.getRoot()->hasElement("test20"));
  EXPECT_TRUE(yaml.getRoot()->hasElement("test22"));

  yaml.clear();

  EXPECT_TRUE(yaml.getRoot() == nullptr);
}

} // namespace