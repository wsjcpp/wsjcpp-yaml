#include <array>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <wsjcpp_yaml.h>

namespace wsjcpp {
namespace yaml {
namespace {

static const std::string sTestYaml = "# Some comment 1\n"
                                     "map1: \n"
                                     "  map11: \n"
                                     "    sss: \n"
                                     "    map111: \n"
                                     "      param1111: v1111\n"
                                     "      param1112: v1112\n"
                                     "    map112: \n"
                                     "      param1121: v1121\n"
                                     "      param1122: v1122\n"
                                     "    map113: \n"
                                     "      param1131: v1131\n"
                                     "      param1132: v1132\n"
                                     "  map12: \n"
                                     "    param121: v121\n"
                                     "    param122: v122\n"
                                     "    map123: \n"
                                     "      param1231: v1231\n"
                                     "      param1232: v1232\n"
                                     "    param1232: v1232\n"
                                     "param2: v2 # some comment 2\n"
                                     "arr1: # some comment array 1\n"
                                     "  - some1\n"
                                     "  - 3\n"
                                     "\n"
                                     "  - Yes\n"
                                     "  # empty\n"
                                     "  - no\n"
                                     "  - true\n"
                                     "  - False\n"
                                     "\n" // empty line
    ;

class WsjcppYamlCursorTest : public testing::Test {
protected:
  void SetUp() override {
    std::string sError;
    ASSERT_TRUE(yaml.loadFromString("test_cursor", sTestYaml, sError));
  }

protected:
  WsjcppYaml yaml;
};

TEST_F(WsjcppYamlCursorTest, ValueTypesTest) {

  static const auto check_value_type = [](const WsjcppYamlCursor &cursor, const std::array<bool, 5> &checkers) {
    EXPECT_EQ(cursor.isNull(), checkers[0]);
    EXPECT_EQ(cursor.isUndefined(), checkers[1]);
    EXPECT_EQ(cursor.isValue(), checkers[2]);
    EXPECT_EQ(cursor.isArray(), checkers[3]);
    EXPECT_EQ(cursor.isMap(), checkers[4]);
  };

  // checking order: isNull, isUndefined, isValue, isArray, isMap
  check_value_type(yaml["map1"], {false, false, false, false, true});                                 // isMap
  check_value_type(yaml["map1-1111"], {true, false, false, false, false});                            // isNull
  check_value_type(yaml["arr1"], {false, false, false, true, false});                                 // isArray
  check_value_type(yaml["map1"]["map11"]["sss"], {false, true, false, false, false});                 // isUndefined
  check_value_type(yaml["map1"]["map11"]["map111"]["param1111"], {false, false, true, false, false}); // isValue
}

TEST_F(WsjcppYamlCursorTest, CollectionsConversionsTest) {
  EXPECT_TRUE(yaml["map1"][0].isNull()) << "map using as array error";
  EXPECT_TRUE(yaml["arr1"]["0"].isNull()) << "array using as map error";
  EXPECT_FALSE(yaml["arr1"][0].isNull()) << "array using as array error";
}

TEST_F(WsjcppYamlCursorTest, ArrayStringTest) {
  EXPECT_EQ(yaml["arr1"].comment(), "some comment array 1");
  EXPECT_EQ(yaml["arr1"].size(), 6);

  const std::vector<std::string> strings_for_check{"some1", "3", "Yes", "no", "true", "False"};
  for (int i = 0; i < strings_for_check.size(); ++i) {
    EXPECT_EQ(yaml["arr1"][i].valStr(), strings_for_check[i]);
  }

  const std::string new_value{"different value"};
  const std::string new_comment{"1234"};
  yaml["arr1"][0].val(new_value).comment(new_comment);
  EXPECT_EQ(yaml["arr1"][0].valStr(), new_value);
  EXPECT_EQ(yaml["arr1"][0].comment(), new_comment);
}

TEST_F(WsjcppYamlCursorTest, ArrayBoolTest) {
  EXPECT_TRUE(yaml["arr1"][2].valBool());
  EXPECT_FALSE(yaml["arr1"][3].valBool());
  EXPECT_TRUE(yaml["arr1"][4].valBool());
  EXPECT_FALSE(yaml["arr1"][5].valBool());

  const std::string str_true{"true"};
  const std::string str_yes{"yes"};
  const std::string str_no{"no"};

  EXPECT_EQ(yaml["arr1"][4].valStr(), str_true);
  EXPECT_EQ(yaml["arr1"][4].node()->getValue(), str_true);
  EXPECT_TRUE(yaml["arr1"][4].valBool());

  static const auto check_bool_value = [&](const WsjcppYamlCursor &cursor, const bool target) {
    EXPECT_EQ(cursor.valBool(), target);
    EXPECT_EQ(cursor.valStr(), (target ? str_yes : str_no));
  };

  yaml["arr1"][4].val(true);
  check_bool_value(yaml["arr1"][4], true);

  yaml["arr1"][4].val(false);
  check_bool_value(yaml["arr1"][4], false);
}

TEST_F(WsjcppYamlCursorTest, ArrayIntTest) {
  EXPECT_EQ(yaml["arr1"][1].valInt(), 3);
  yaml["arr1"][1].val(10);
  EXPECT_EQ(yaml["arr1"][1].valInt(), 10);
}

TEST_F(WsjcppYamlCursorTest, MapTest) {
  ASSERT_TRUE(yaml["map1"]["map12"].isMap());

  const std::vector<std::string> expected_keys{"param121", "param122", "map123", "param1232"};
  const std::vector<std::string> actual_keys = yaml["map1"]["map12"].keys();
  EXPECT_EQ(actual_keys, expected_keys);

  EXPECT_FALSE(yaml["map1"]["map12"].hasKey("some"));
  EXPECT_TRUE(yaml["map1"]["map12"].hasKey("map123"));
  EXPECT_FALSE(yaml["map1"]["map12"]["map123"].isValue());
  EXPECT_TRUE(yaml["map1"]["map12"]["param122"].isValue());
}

} // namespace
} // namespace yaml
} // namespace wsjcpp