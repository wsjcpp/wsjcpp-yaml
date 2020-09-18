#ifndef UNIT_TEST_LINE_PARSER_H
#define UNIT_TEST_LINE_PARSER_H

#include <wsjcpp_unit_tests.h>

class UnitTestLineParser : public WsjcppUnitTestBase {
    public:
        UnitTestLineParser();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_LINE_PARSER_H