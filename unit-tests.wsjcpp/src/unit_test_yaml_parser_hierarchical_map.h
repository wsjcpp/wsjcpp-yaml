#ifndef UNIT_TEST_YAML_PARSER_HIERARCHICAL_MAP_H
#define UNIT_TEST_YAML_PARSER_HIERARCHICAL_MAP_H

#include <wsjcpp_unit_tests.h>

class UnitTestYamlParserHierarchicalMap : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserHierarchicalMap();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_YAML_PARSER_HIERARCHICAL_MAP_H