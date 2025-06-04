#include <iostream>
#include <wsjcpp_yaml.h>

int main() {
     struct LineTest {
        LineTest(
            int nNumberOfTest,
            std::string sLine,
            std::string sPrefix,
            bool isArrayItem,
            std::string sName,
            WsjcppYamlQuotes nNameQuotes,
            std::string sValue,
            WsjcppYamlQuotes nValueQuotes,
            std::string sComment
        ) : nNumberOfTest(nNumberOfTest),
            sLine(sLine),
            sPrefix(sPrefix),
            isArrayItem(isArrayItem),
            sName(sName),
            nNameQuotes(nNameQuotes),
            sValue(sValue),
            nValueQuotes(nValueQuotes),
            sComment(sComment)
        {
            //    
        };
        int nNumberOfTest;
        std::string sLine;
        std::string sPrefix;
        bool isArrayItem;
        std::string sName;
        WsjcppYamlQuotes nNameQuotes;
        std::string sValue;
        WsjcppYamlQuotes nValueQuotes;
        std::string sComment;
    };

    std::vector<LineTest> vTestLines;

    vTestLines.push_back(LineTest(1,
        "# Some comment 1 ", "",
        false, // array node
        "", WSJCPP_YAML_QUOTES_NONE, // name
        "", WSJCPP_YAML_QUOTES_NONE, // value
        "Some comment 1" // comment
    ));
    vTestLines.push_back(LineTest(2,
        "  test2: \"t\\\"wo\" # some comment 2  ", "  ",
        false,  // array node
        "test2", WSJCPP_YAML_QUOTES_NONE, // name
        "t\"wo", WSJCPP_YAML_QUOTES_DOUBLE, // value
        "some comment 2" // comment
    ));
    vTestLines.push_back(LineTest(3, 
        "  test3:", "  ",
        false, // array node
        "test3", WSJCPP_YAML_QUOTES_NONE, // name
        "", WSJCPP_YAML_QUOTES_NONE, // value
        "" // comment
    ));
    vTestLines.push_back(LineTest(4,
        "  - test4", "  ",
        true,  // array node
        "", WSJCPP_YAML_QUOTES_NONE, // name
        "test4", WSJCPP_YAML_QUOTES_NONE, // value
        "" // comment
    ));
    vTestLines.push_back(LineTest(5,
        "", "",
        false, // array node
        "", WSJCPP_YAML_QUOTES_NONE, // name
        "", WSJCPP_YAML_QUOTES_NONE, // value
        "" // comment
    ));
    vTestLines.push_back(LineTest(6,
        "  - \"test4:111\"", "  ",
        true, // array node
        "", WSJCPP_YAML_QUOTES_NONE, // name
        "test4:111", WSJCPP_YAML_QUOTES_DOUBLE, // value
        "" // comment
    ));
    vTestLines.push_back(LineTest(7,
        "issues: https://github.com/wsjcpp/wsjcpp-yaml/issues", "",
        false, // array node
        "issues", WSJCPP_YAML_QUOTES_NONE,  // name
        "https://github.com/wsjcpp/wsjcpp-yaml/issues", WSJCPP_YAML_QUOTES_NONE, // value
        "" // comment
    ));

    int ret = 0;

    for (int i = 0; i < vTestLines.size(); i++) {
        LineTest test = vTestLines[i];
        std::string tagline = "{line:" + std::to_string(test.nNumberOfTest) + ": '" + test.sLine + "'}";

        WsjcppYamlParsebleLine line(test.nNumberOfTest);
        std::string sError;
            // compare(tagline + ", parseLine",
        if (!line.parseLine(test.sLine, sError)) {
            std::cerr << tagline << ", parseLine: " << sError << std::endl;
            ret = -1;
            continue;
        }

        if (line.getPrefix() != test.sPrefix) {
            std::cerr << tagline << ", prefix expected '" << test.sPrefix << "', but got '" << line.getPrefix() << "'" << std::endl;
            ret = -1;
        }

        if (line.isArrayItem() != test.isArrayItem) {
            std::cerr << tagline << ", arrayitem expected" << std::endl;
            ret = -1;
        }

        if (line.getName() != test.sName) {
            std::cerr << tagline << ", name expected '" << test.sName << "', but got '" << line.getName() << "'" << std::endl;
            ret = -1;
        }

        if (line.getValue() != test.sValue) {
            std::cerr << tagline << ", value expected '" << test.sValue << "', but got '" << line.getValue() << "'" << std::endl;
            ret = -1;
        }

        if (line.getComment() != test.sComment) {
            std::cerr << tagline << ", comment expected '" << test.sComment << "', but got '" << line.getComment() << "'" << std::endl;
            ret = -1;
        }

        if (line.getNameQuotes() != test.nNameQuotes) {
            std::cerr << tagline << ", name-has-quotes expected" << std::endl;
            ret = -1;
        }

        if (line.getValueQuotes() != test.nValueQuotes) {
            std::cerr << tagline << ", value-quotes expected" << std::endl;
            ret = -1;
        }
    }
    return ret;
}