#include <string_view>

#include <gtest/gtest.h>

#include <wsjcpp/yaml/yaml.h>

using namespace std::string_view_literals;

namespace {

// Demonstrate some basic assertions.
TEST(WsjcppYamlTest, AppendElements) {
  static constexpr std::string_view expected_yaml_string = R"(p1: val1
some:
  p2: val2
  sub-some:
    p3: val3
  arr-some:
    - 1234
    - p4: val4
      p5: val5
p6: val6)"sv;

  WsjcppYaml yaml;
  yaml.getRoot()->setElementValue("p1", "val1");
  yaml.getRoot()->createElementMap("some");
  WsjcppYamlNode *pSome = yaml.getRoot()->getElement("some");
  pSome->setElementValue("p2", "val2");
  pSome->createElementMap("sub-some");
  WsjcppYamlNode *pSubSome = pSome->getElement("sub-some");
  pSubSome->setElementValue("p3", "val3");
  pSome->createElementArray("arr-some");
  WsjcppYamlNode *pArrSome = pSome->getElement("arr-some");
  pArrSome->appendElementValue("1234");
  WsjcppYamlPlaceInFile placeInFile;
  WsjcppYamlNode *pItemMap = new WsjcppYamlNode(pArrSome, &yaml, placeInFile, WSJCPP_YAML_NODE_MAP);
  pArrSome->appendElement(pItemMap);
  pItemMap->setElementValue("p4", "val4");
  pItemMap->setElementValue("p5", "val5");
  yaml.getRoot()->setElementValue("p6", "val6");

  EXPECT_EQ(yaml.getRoot()->toString(), expected_yaml_string);
}

TEST(WsjcppYamlTest, Cleanup) {
  static constexpr std::string_view sTestYaml1 = R"(# Some comment 1
test10: one
test20: two # some comment 2)"sv;

  static constexpr std::string_view sTestYaml2 = R"(# Some comment 1
test11: one
test20: two # some comment 2
test22: two # some comment 2)"sv;

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