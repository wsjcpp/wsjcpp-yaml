#ifndef UNIT_TEST_YAML_PARSER_ARRAY_INCLUDED_MAP_H
#define UNIT_TEST_YAML_PARSER_ARRAY_INCLUDED_MAP_H

#include <wsjcpp_unit_tests.h>

class UnitTestYamlParserArrayIncludedMap : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserArrayIncludedMap();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_YAML_PARSER_ARRAY_INCLUDED_MAP_H