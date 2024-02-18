#include <string_view>
#include <string>
#include <gtest/gtest.h>
#include <wsjcpp_yaml.h>

namespace {

// Demonstrate some basic assertions.
TEST(WsjcppYamlTest, AppendElements) {
  static const std::string expected_yaml_string = "p1: val1\n"
    "some:\n"
    "  p2: val2\n"
    "  sub-some:\n"
    "    p3: val3\n"
    "  arr-some:\n"
    "    - 1234\n"
    "    - p4: val4\n"
    "      p5: val5\n"
    "p6: val6";

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

} // namespace