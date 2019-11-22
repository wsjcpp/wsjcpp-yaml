#ifndef UNIT_TEST_YAML_PARSER_H
#define UNIT_TEST_YAML_PARSER_H

#include <unit_tests.h>

class UnitTestYamlParser : public UnitTestBase {
    public:
        UnitTestYamlParser();
        virtual void init();
        virtual bool run();
};

#endif // UNIT_TEST_YAML_PARSER_H