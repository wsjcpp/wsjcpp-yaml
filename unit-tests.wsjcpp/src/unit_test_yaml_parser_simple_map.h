#ifndef UNIT_TEST_YAML_PARSER_SIMPLE_MAP_H
#define UNIT_TEST_YAML_PARSER_SIMPLE_MAP_H

#include <wsjcpp_unit_tests.h>

class UnitTestYamlParserSimpleMap : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserSimpleMap();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_YAML_PARSER_SIMPLE_MAP_H