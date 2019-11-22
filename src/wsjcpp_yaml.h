#ifndef WSJCPP_YAML_H
#define WSJCPP_YAML_H

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ---------------------------------------------------------------------

enum WSJCppYAMLItemType {
    WSJCPP_YAML_ITEM_UNDEFINED,
    WSJCPP_YAML_ITEM_EMPTY,
    WSJCPP_YAML_ITEM_ARRAY,
    WSJCPP_YAML_ITEM_MAP,
    WSJCPP_YAML_ITEM_VALUE
};

// ---------------------------------------------------------------------

class WSJCppYAMLItem {
    public:
        WSJCppYAMLItem(
            WSJCppYAMLItem *pParent,
            int nOriginalNumberOfLine, 
            const std::string &sOriginalLine,
            WSJCppYAMLItemType nItemType
        );
        ~WSJCppYAMLItem();
        WSJCppYAMLItem *getParent();
        std::string getOriginalLine();
        int getOriginalNumberOfLine();

        void setComment(const std::string &sComment);
        std::string getComment();

        void setName(const std::string &sName);
        std::string getName();

        bool isEmpty();
        void doEmpty();

        bool isUndefined();
        void doArray();
        void doMap();

        bool isMap();
        bool hasElement(const std::string &sName);
        WSJCppYAMLItem *getElement(const std::string &sName);
        bool setElement(const std::string &sName, WSJCppYAMLItem *pItem);
        bool removeElement(const std::string &sName);

        bool isArray();
        int getLength();
        WSJCppYAMLItem *getElement(int i);
        bool appendElement(WSJCppYAMLItem *pItem);

        bool isValue();
        std::string getValue();
        void setValue(const std::string &sValue);

        std::string toString();
        std::string getItemTypeAsString();

    private:
        std::string TAG;
        WSJCppYAMLItem *m_pParent;
        int m_nOriginalNumberOfLine;
        std::string m_sOriginalLine;
        WSJCppYAMLItemType m_nItemType;
        std::vector<WSJCppYAMLItem *> m_vObjects;
        std::string m_sValue; // if it is not array or map
        std::string m_sName;
        std::string m_sComment;
        
};

// ---------------------------------------------------------------------

enum WSJCppYAMLParserLineStates {
    NO,
    NAME_AND_VALUE,
    COMMENT,
    STRING,
    ESCAPING
};

// ---------------------------------------------------------------------

class WSJCppYAMLParsebleLine {
    public:
        WSJCppYAMLParsebleLine(int nLine);
        WSJCppYAMLParsebleLine();
        int getLineNumber();

        std::string getPrefix();
        int getIntent(); // prefix length
        bool isArrayItem();
        std::string getComment();
        std::string getName();
        bool isEmptyName();
        std::string getValue();
        bool isEmptyValue();

        void parseLine(const std::string &sLine);

    private:
        std::string TAG;
        int m_nLine;

        std::string m_sPrefix;
        bool m_bArrayItem;
        std::string m_sComment;
        std::string m_sNameAndValue;
        std::string m_sName;
        std::string m_sValue;
        bool m_bNameWasWithQuotes;
        bool m_bValueWasWithQuotes;

        std::string removeStringDoubleQuotes(const std::string &sValue);
};

// ---------------------------------------------------------------------

class WSJCppYAMLParserStatus {
    public:
        int nIntent;
        int nLine;
        WSJCppYAMLItem *pCurItem;
        WSJCppYAMLParsebleLine line;
        std::string sLine;

        void logUnknownLine(const std::string &sPrefix);
};

// ---------------------------------------------------------------------

class WSJCppYAML {
    public:
        WSJCppYAML();
        ~WSJCppYAML();
        bool loadFromFile(const std::string &sFileName);
        bool saveToFile(const std::string &sFileName);
        bool loadFromString(const std::string &sBuffer);
        bool loadFromString(std::string &sBuffer);
        bool saveToString(std::string &sBuffer);
        WSJCppYAMLItem *getRoot();

    private:
        std::string TAG;
        
        std::vector<std::string> splitToLines(const std::string &sBuffer);
        bool parse(const std::string &sBuffer);
        void process_sameIntent_hasName_emptyValue_arrayItem(WSJCppYAMLParserStatus &st);
        void process_sameIntent_hasName_emptyValue_noArrayItem(WSJCppYAMLParserStatus &st);
        void process_sameIntent_hasName_hasValue_arrayItem(WSJCppYAMLParserStatus &st);
        void process_sameIntent_hasName_hasValue_noArrayItem(WSJCppYAMLParserStatus &st);
        void process_sameIntent_emptyName_hasValue_arrayItem(WSJCppYAMLParserStatus &st);
        void process_sameIntent_emptyName_hasValue_noArrayItem(WSJCppYAMLParserStatus &st);
        void process_sameIntent_emptyName_emptyValue_arrayItem(WSJCppYAMLParserStatus &st);
        void process_sameIntent_emptyName_emptyValue_noArrayItem(WSJCppYAMLParserStatus &st);

        std::vector<std::string> m_sLines;
        WSJCppYAMLItem *m_pRoot;
};

#endif // WSJCPP_YAML_H