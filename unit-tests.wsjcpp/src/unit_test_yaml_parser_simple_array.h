#ifndef UNIT_TEST_YAML_PARSER_SIMPLE_ARRAY_H
#define UNIT_TEST_YAML_PARSER_SIMPLE_ARRAY_H

#include <wsjcpp_unit_tests.h>

class UnitTestYamlParserSimpleArray : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserSimpleArray();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_YAML_PARSER_SIMPLE_ARRAY_H