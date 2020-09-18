#ifndef UNIT_TEST_YAML_PARSER_QUOTES_H
#define UNIT_TEST_YAML_PARSER_QUOTES_H

#include <wsjcpp_unit_tests.h>

class UnitTestYamlParserQuotes : public WsjcppUnitTestBase {
    public:
        UnitTestYamlParserQuotes();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_YAML_PARSER_QUOTES_H