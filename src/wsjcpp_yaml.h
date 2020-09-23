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

enum WsjcppYamlItemType {
    WSJCPP_YAML_ITEM_UNDEFINED,
    WSJCPP_YAML_ITEM_EMPTY,
    WSJCPP_YAML_ITEM_ARRAY,
    WSJCPP_YAML_ITEM_MAP,
    WSJCPP_YAML_ITEM_VALUE
};

// ---------------------------------------------------------------------

class WsjcppYamlPlaceInFile {
    public:
        WsjcppYamlPlaceInFile();
        WsjcppYamlPlaceInFile(const std::string &sFilename, int nNumberOfLine, const std::string &sLine);

        std::string getFilename() const;
        void setFilename(const std::string &sFilename);

        int getNumberOfLine() const;
        void setNumberOfLine(int nNumberOfLine);

        std::string getLine() const;
        void setLine(const std::string &sLine);
        std::string getForLogFormat();

    private:
        std::string m_sFilename;
        int m_nNumberOfLine;
        std::string m_sLine;
};

// ---------------------------------------------------------------------
// WsjcppYamlQuotes

enum WsjcppYamlQuotes {
    WSJCPP_YAML_QUOTES_NONE,
    WSJCPP_YAML_QUOTES_DOUBLE,
    WSJCPP_YAML_QUOTES_SINGLE
};

// ---------------------------------------------------------------------
/*!
	\brief Class for keep data of yaml node

	Basic class for yaml tree
*/

class WsjcppYamlItem { // TODO: rename to node
    public:
        WsjcppYamlItem(
            WsjcppYamlItem *pParent,
            const WsjcppYamlPlaceInFile &placeInFile,
            WsjcppYamlItemType nItemType
        );
        ~WsjcppYamlItem();
        WsjcppYamlItem *getParent();

        WsjcppYamlPlaceInFile getPlaceInFile();
        void setPlaceInFile(const WsjcppYamlPlaceInFile &placeInFile);

        void setComment(const std::string &sComment);
        std::string getComment();

        void setName(const std::string &sName, WsjcppYamlQuotes nNameQuotes = WSJCPP_YAML_QUOTES_NONE);
        std::string getName();
        WsjcppYamlQuotes getNameQuotes();

        bool isEmpty();
        void doEmpty();

        bool isUndefined();
        void doArray();
        void doMap();
        void doValue();

        bool isMap();
        bool hasElement(const std::string &sName);
        WsjcppYamlItem *getElement(const std::string &sName);
        bool setElement(const std::string &sName, WsjcppYamlItem *pItem);
        bool removeElement(const std::string &sName);
        std::vector<std::string> getKeys();

        bool setElementValue(
            const std::string &sName, const std::string &sValue,
            WsjcppYamlQuotes nNameQuotes = WSJCPP_YAML_QUOTES_NONE,
            WsjcppYamlQuotes nValueQuotes = WSJCPP_YAML_QUOTES_NONE
        );

        bool setElementValue(
            const std::string &sName, int nValue,
            WsjcppYamlQuotes nNameQuotes = WSJCPP_YAML_QUOTES_NONE,
            WsjcppYamlQuotes nValueQuotes = WSJCPP_YAML_QUOTES_NONE
        );

        bool setElementValue(
            const std::string &sName, long nValue,
            WsjcppYamlQuotes nNameQuotes = WSJCPP_YAML_QUOTES_NONE,
            WsjcppYamlQuotes nValueQuotes = WSJCPP_YAML_QUOTES_NONE
        );

        bool setElementValue(
            const std::string &sName, bool bValue,
            WsjcppYamlQuotes nNameQuotes = WSJCPP_YAML_QUOTES_NONE,
            WsjcppYamlQuotes nValueQuotes = WSJCPP_YAML_QUOTES_NONE
        );

        bool createElementMap(const std::string &sName, WsjcppYamlQuotes nNameQuotes);
        WsjcppYamlItem *createElementMap();
        bool createElementArray(const std::string &sName, WsjcppYamlQuotes nNameQuotes);

        bool isArray();
        int getLength();
        WsjcppYamlItem *getElement(int i);
        bool appendElement(WsjcppYamlItem *pItem);
        bool appendElementValue(const std::string &sValue, WsjcppYamlQuotes nValueQuotes = WSJCPP_YAML_QUOTES_NONE);
        bool removeElement(int i);

        bool isValue();
        
        std::string getValue(); // deprecated
        std::string getStringValue(); // simular 'getValue'
        bool getBoolValue();
        long getLongValue();
        int getIntValue();

        void setValue(const std::string &sValue, WsjcppYamlQuotes nQuotes = WSJCPP_YAML_QUOTES_NONE);
        WsjcppYamlQuotes getValueQuotes();

        std::string toString(std::string sIntent = "");
        std::string getItemTypeAsString();

        std::string getForLogFormat();

    private:
        std::string TAG;
        WsjcppYamlItem *m_pParent;
        WsjcppYamlPlaceInFile m_placeInFile;
        WsjcppYamlItemType m_nItemType;
        std::vector<WsjcppYamlItem *> m_vObjects;
        std::string m_sValue; // if it is not array or map
        WsjcppYamlQuotes m_nValueQuotes;
        std::string m_sName;
        WsjcppYamlQuotes m_nNameQuotes;
        
        std::string m_sComment;
};

// ---------------------------------------------------------------------

class WsjcppYamlParsebleLine {
    public:
        WsjcppYamlParsebleLine(int nLine);
        WsjcppYamlParsebleLine();
        int getLineNumber();

        std::string getPrefix();
        int getIntent(); // prefix length
        bool isArrayItem();
        std::string getComment();
        bool hasComment();
        std::string getName();
        WsjcppYamlQuotes getNameQuotes();
        bool isEmptyName();
        std::string getValue();
        WsjcppYamlQuotes getValueQuotes();
        bool isEmptyValue();
        bool isEmptyLine();

        bool parseLine(const std::string &sLine, std::string &sError);

    private:
        std::string TAG;
        int m_nLineNumber;

        std::string m_sPrefix;
        bool m_bArrayItem;
        std::string m_sComment;
        std::string m_sName;
        std::string m_sValue;
        WsjcppYamlQuotes m_nNameQuotes;
        WsjcppYamlQuotes m_nValueQuotes;
        bool m_bHasComment;
        bool m_bEmptyLine;

        std::string removeStringDoubleQuotes(const std::string &sValue);
        std::string removeStringSingleQuotes(const std::string &sValue);
};

// ---------------------------------------------------------------------

class WsjcppYamlParserStatus {
    public:
        int nIntent;
        WsjcppYamlItem *pCurItem;
        WsjcppYamlParsebleLine line;
        WsjcppYamlPlaceInFile placeInFile;
        void logUnknownLine(const std::string &sPrefix);
};


// ---------------------------------------------------------------------

class WsjcppYamlCursor {
    public:
        WsjcppYamlCursor(WsjcppYamlItem *pCurrentNode);
        WsjcppYamlCursor();
        ~WsjcppYamlCursor();

        // null or undefined
        bool isNull() const;
        
        // array
        bool isArray() const;
        size_t size() const;
        WsjcppYamlCursor &push(const std::string &sVal);
        WsjcppYamlCursor &push(int nVal);
        WsjcppYamlCursor &push(bool bVal);
        WsjcppYamlCursor &remove(int nIdx);

        // map
        bool isMap() const;
        std::vector<std::string> keys();
        WsjcppYamlCursor &set(const std::string &sName, const std::string &sValue);
        WsjcppYamlCursor &set(const std::string &sName, int nValue);
        WsjcppYamlCursor &set(const std::string &sName, bool bValue);
        WsjcppYamlCursor &remove(const std::string &sKey);

        // comment 
        std::string comment();
        WsjcppYamlCursor &comment(const std::string& sComment);
        
        // val
        std::string valStr();
        WsjcppYamlCursor &val(const std::string &sValue);
        bool valInt();
        WsjcppYamlCursor &val(int nValue);
        bool valBool();
        WsjcppYamlCursor &val(bool bValue);
       

        WsjcppYamlCursor operator[](int idx) const;
        WsjcppYamlCursor operator[](const std::string &sName) const;

    private:
        WsjcppYamlItem *m_pCurrentNode;
};


// ---------------------------------------------------------------------

class WsjcppYaml {
    public:
        WsjcppYaml();
        ~WsjcppYaml();
        bool loadFromFile(const std::string &sFileName, std::string &sError);
        bool saveToFile(const std::string &sFileName);
        bool loadFromString(const std::string &sBufferName, const std::string &sBuffer, std::string &sError);
        bool saveToString(std::string &sBuffer);
        WsjcppYamlItem *getRoot();

        WsjcppYamlCursor getCursor() const;
        WsjcppYamlCursor operator[](int idx) const;
        WsjcppYamlCursor operator[](const std::string &sName) const;

    private:
        std::string TAG;
        
        // TODO replace to WsjcppCore::split()
        std::vector<std::string> splitToLines(const std::string &sBuffer);
        bool parse(const std::string &sFileName, const std::string &sBuffer, std::string &sError);
        void process_sameIntent_hasName_emptyValue_arrayItem(WsjcppYamlParserStatus &st);
        void process_sameIntent_hasName_emptyValue_noArrayItem(WsjcppYamlParserStatus &st);
        void process_sameIntent_hasName_hasValue_arrayItem(WsjcppYamlParserStatus &st);
        void process_sameIntent_hasName_hasValue_noArrayItem(WsjcppYamlParserStatus &st);
        void process_sameIntent_emptyName_hasValue_arrayItem(WsjcppYamlParserStatus &st);
        void process_sameIntent_emptyName_hasValue_noArrayItem(WsjcppYamlParserStatus &st);
        void process_sameIntent_emptyName_emptyValue_arrayItem(WsjcppYamlParserStatus &st);
        void process_sameIntent_emptyName_emptyValue_noArrayItem(WsjcppYamlParserStatus &st);

        std::vector<std::string> m_sLines;
        WsjcppYamlItem *m_pRoot;
};

#endif // WSJCPP_YAML_H

