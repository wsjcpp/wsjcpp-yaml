#ifndef UNIT_TEST_YAML_PARSER_COMMENTS_H
#define UNIT_TEST_YAML_PARSER_COMMENTS_H

#include <wsjcpp_unit_tests.h>

class UnitTestYamlParserComments : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserComments();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_YAML_PARSER_COMMENTS_H