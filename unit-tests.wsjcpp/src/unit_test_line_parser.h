#ifndef UNIT_TEST_LINE_PARSER_H
#define UNIT_TEST_LINE_PARSER_H

#include <wsjcpp_unit_tests.h>

class UnitTestLineParser : public WsjcppUnitTestBase {
    public:
        UnitTestLineParser();
        virtual void init();
        virtual bool run();
};

#endif // UNIT_TEST_LINE_PARSER_H