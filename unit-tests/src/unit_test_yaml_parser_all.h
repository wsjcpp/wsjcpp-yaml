#ifndef UNIT_TEST_YAML_PARSER_ALL_H
#define UNIT_TEST_YAML_PARSER_ALL_H

#include <unit_tests.h>

class UnitTestYamlParserAll : public UnitTestBase {
    public:
        UnitTestYamlParserAll();
        virtual void init();
        virtual bool run();
};

#endif // UNIT_TEST_YAML_PARSER_ALL_H