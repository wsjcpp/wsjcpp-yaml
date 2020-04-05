#ifndef UNIT_TEST_YAML_PARSER_ALL_H
#define UNIT_TEST_YAML_PARSER_ALL_H

#include <wsjcpp_unit_tests.h>

class UnitTestYamlParserAll : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserAll();
        virtual void init();
        virtual bool run();
};

#endif // UNIT_TEST_YAML_PARSER_ALL_H