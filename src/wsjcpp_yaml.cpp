
#include "wsjcpp_yaml.h"
#include <wsjcpp_core.h>
#include <cstdlib>

// ---------------------------------------------------------------------
// WsjcppYamlPlaceInFile

WsjcppYamlPlaceInFile::WsjcppYamlPlaceInFile() {
    m_sFilename = "";
    m_nNumberOfLine = 0;
    m_sLine = "";
}

// ---------------------------------------------------------------------

WsjcppYamlPlaceInFile::WsjcppYamlPlaceInFile(const std::string &sFilename, int nNumberOfLine, const std::string &sLine) {
    m_sFilename = sFilename;
    m_nNumberOfLine = nNumberOfLine;
    m_sLine = sLine;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlPlaceInFile::getFilename() const {
    return m_sFilename;
}

// ---------------------------------------------------------------------

void WsjcppYamlPlaceInFile::setFilename(const std::string &sFilename) {
    m_sFilename = sFilename;
}

// ---------------------------------------------------------------------

int WsjcppYamlPlaceInFile::getNumberOfLine() const {
    return m_nNumberOfLine;
}

// ---------------------------------------------------------------------

void WsjcppYamlPlaceInFile::setNumberOfLine(int nNumberOfLine) {
    m_nNumberOfLine = nNumberOfLine;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlPlaceInFile::getLine() const {
    return m_sLine;
}

// ---------------------------------------------------------------------

void WsjcppYamlPlaceInFile::setLine(const std::string &sLine) {
    m_sLine = sLine;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlPlaceInFile::getForLogFormat() {
    return "(" + m_sFilename + ":" + std::to_string(m_nNumberOfLine + 1) + "): " + m_sLine;
}

// ---------------------------------------------------------------------
// WsjcppYamlItem

WsjcppYamlItem::WsjcppYamlItem(
    WsjcppYamlItem *pParent, 
    const WsjcppYamlPlaceInFile &placeInFile,
    WsjcppYamlItemType nItemType
) {
    m_pParent = pParent;
    m_placeInFile.setFilename(placeInFile.getFilename());
    m_placeInFile.setLine(placeInFile.getLine());
    m_placeInFile.setNumberOfLine(placeInFile.getNumberOfLine());
    m_nItemType = nItemType;
    m_nValueQuotes = WSJCPP_YAML_QUOTES_NONE;
    m_nNameQuotes = WSJCPP_YAML_QUOTES_NONE;
    TAG = "WsjcppYamlNode";
}

// ---------------------------------------------------------------------

WsjcppYamlItem::~WsjcppYamlItem() {
     for (int i = 0; i < m_vObjects.size(); i++) {
        delete m_vObjects[i];
    }
    m_vObjects.clear();
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppYamlItem::getParent() {
    return m_pParent;
}

// ---------------------------------------------------------------------

WsjcppYamlPlaceInFile WsjcppYamlItem::getPlaceInFile() {
    return m_placeInFile;
}

// ---------------------------------------------------------------------

void WsjcppYamlItem::setPlaceInFile(const WsjcppYamlPlaceInFile &placeInFile) {
    m_placeInFile.setFilename(placeInFile.getFilename());
    m_placeInFile.setLine(placeInFile.getLine());
    m_placeInFile.setNumberOfLine(placeInFile.getNumberOfLine());
}

// ---------------------------------------------------------------------

void WsjcppYamlItem::setComment(const std::string &sComment) {
    m_sComment = sComment;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlItem::getComment() {
    return m_sComment;
}

// ---------------------------------------------------------------------

void WsjcppYamlItem::setName(const std::string &sName, WsjcppYamlQuotes nNameQuotes) {
    m_sName = sName;
    m_nNameQuotes = nNameQuotes;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlItem::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

WsjcppYamlQuotes WsjcppYamlItem::getNameQuotes() {
    return m_nNameQuotes;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::isEmpty() {
    return m_nItemType == WSJCPP_YAML_ITEM_EMPTY;
}

// ---------------------------------------------------------------------

void WsjcppYamlItem::doEmpty() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_EMPTY;
    } else {
        WsjcppLog::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::isUndefined() {
    return m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED;
}

// ---------------------------------------------------------------------

void WsjcppYamlItem::doArray() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_ARRAY;
    } else {
        WsjcppLog::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

void WsjcppYamlItem::doMap() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_MAP;
    } else {
        WsjcppLog::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

void WsjcppYamlItem::doValue() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_VALUE;
    } else {
        WsjcppLog::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::isMap() {
    return m_nItemType == WSJCPP_YAML_ITEM_MAP;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::hasElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WsjcppLog::throw_err(TAG, "hasElement('" + sName + "'): Element must be map");
    }
    for (int i = 0; i < m_vObjects.size(); i++) {
        if (m_vObjects[i]->getName() == sName) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppYamlItem::getElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WsjcppLog::throw_err(TAG, "getElement: Element must be map");
    }
    
    for (int i = 0; i < m_vObjects.size(); i++) {
        std::string sObjectName = m_vObjects[i]->getName();
        if (m_vObjects[i]->getName() == sName) {
            return m_vObjects[i];
        }
    }
    WsjcppLog::throw_err(TAG, "Element '" + sName + "' not found for " + this->getForLogFormat());  
    return nullptr;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::setElement(const std::string &sName, WsjcppYamlItem *pItem) {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_MAP; // change item type to map on first element  
    }

    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WsjcppLog::throw_err(TAG, "setElement, Element must be 'map' for " + pItem->getPlaceInFile().getForLogFormat());
    }
    
    if (this->hasElement(sName)) { // TODO remove previous element
        WsjcppLog::throw_err(TAG, "setElement: Map already has element with this name: '" + sName + "'");
    }
    m_vObjects.push_back(pItem); // TODO create clone
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::removeElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WsjcppLog::throw_err(TAG, "removeElement: Element must be map");
    }
    std::vector<WsjcppYamlItem *>::iterator it;
    for (it = m_vObjects.begin(); it != m_vObjects.end(); ++it) {
        WsjcppYamlItem *pItem = *it;
        if (pItem->getName() == sName) {
            m_vObjects.erase(it);
            delete pItem;
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

std::vector<std::string> WsjcppYamlItem::getKeys() {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WsjcppLog::throw_err(TAG, "getKeys: Element must be map");
    }
    std::vector<std::string> vKeys;
    for (int i = 0; i < m_vObjects.size(); i++) {
        WsjcppYamlItem *pItem = m_vObjects[i];
        if (pItem->isValue() || pItem->isMap() || pItem->isArray() || pItem->isUndefined()) {
            std::string sName = pItem->getName();
            vKeys.push_back(sName);
        }
    }
    return vKeys;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::setElementValue(
    const std::string &sName,
    const std::string &sValue,
    WsjcppYamlQuotes nNameQuotes,
    WsjcppYamlQuotes nValueQuotes
) {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_MAP; // change item type to map on first element  
    }

    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        WsjcppLog::throw_err(TAG, "setElement, Element must be 'map' for " + this->getPlaceInFile().getForLogFormat());
    }
    
    if (this->hasElement(sName)) {
        WsjcppYamlItem *pItem = this->getElement(sName);
        pItem->setValue(sValue, nValueQuotes);
    } else {
        WsjcppYamlPlaceInFile pl;
        WsjcppYamlItem *pNewItem = new WsjcppYamlItem(this, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_VALUE);
        pNewItem->setName(sName, nNameQuotes);
        pNewItem->setValue(sValue, nValueQuotes);
        this->setElement(sName, pNewItem);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::createElementMap(const std::string &sName, WsjcppYamlQuotes nNameQuotes) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP ) {
        WsjcppLog::throw_err(TAG, "createElementMap, Element must be 'map' for " + this->getPlaceInFile().getForLogFormat());
    }
    if (this->hasElement(sName)) {
        return false; // already exists
    }
    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pNewItem = new WsjcppYamlItem(this, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_MAP);
    pNewItem->setName(sName, nNameQuotes);
    this->setElement(sName, pNewItem);
    return true;
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppYamlItem::createElementMap() {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY ) {
        WsjcppLog::throw_err(TAG, "createElementMap, Element must be 'array' for " + this->getPlaceInFile().getForLogFormat());
    }
    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pNewItem = new WsjcppYamlItem(this, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_MAP);
    this->appendElement(pNewItem);
    return pNewItem;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::createElementArray(const std::string &sName, WsjcppYamlQuotes nNameQuotes) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP ) {
        WsjcppLog::throw_err(TAG, "createElementArray, Element must be 'map' for " + this->getPlaceInFile().getForLogFormat());
    }
    if (this->hasElement(sName)) {
        return false;
    }
    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pNewItem = new WsjcppYamlItem(this, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_ARRAY);
    pNewItem->setName(sName, nNameQuotes);
    this->setElement(sName, pNewItem);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::isArray() {
    return m_nItemType == WSJCPP_YAML_ITEM_ARRAY;
}

// ---------------------------------------------------------------------

int WsjcppYamlItem::getLength() {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WsjcppLog::throw_err(TAG, "getLength, Element must be array for " + this->getForLogFormat());
    }
    int nCount = 0;
    for (int i = 0; i < m_vObjects.size(); i++) {
        if (!m_vObjects[i]->isEmpty()) {
            nCount++;
        }
    }
    return nCount;
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppYamlItem::getElement(int i) {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WsjcppLog::throw_err(TAG, "getElement, Element must be array");
    }
    int nCounter = -1;
    WsjcppYamlItem *pItem = nullptr;
    for (int n = 0; n < m_vObjects.size(); n++) {
        if (!m_vObjects[n]->isEmpty()) {
            nCounter++;
            if (nCounter == i) {
                pItem = m_vObjects[n];
                break; 
            }
        }
    }
    if (pItem == nullptr) {
        WsjcppLog::throw_err(TAG, "getElement(" + std::to_string(i) +  "), Out of range in array for '" + this->getPlaceInFile().getLine() + "'");
    }
    return pItem;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::appendElement(WsjcppYamlItem *pItem) {
    if (pItem->isEmpty()) {
        m_vObjects.push_back(pItem); // TODO clone object
        return true;
    }
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WsjcppLog::throw_err(TAG, "appendElement, Element must be array for " + this->getForLogFormat());
    }
    m_vObjects.push_back(pItem); // TODO clone object
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::appendElementValue(const std::string &sValue, WsjcppYamlQuotes nValueQuotes) {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WsjcppLog::throw_err(TAG, "appendElementValue, Element must be array for " + this->getForLogFormat());
    }
    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pNewItem = new WsjcppYamlItem(this, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_VALUE);
    pNewItem->setValue(sValue, nValueQuotes);
    return this->appendElement(pNewItem);
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::removeElement(int i) {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        WsjcppLog::throw_err(TAG, "appendElement, Element must be array for " + this->getForLogFormat());
    }
    int nCounter = -1;
    WsjcppYamlItem *pItem = nullptr;
    for (int n = 0; n < m_vObjects.size(); n++) {
        if (!m_vObjects[n]->isEmpty()) {
            nCounter++;
            if (nCounter == i) {
                pItem = m_vObjects[n];
                break; 
            }
        }
    }
    if (pItem == nullptr) {
        WsjcppLog::throw_err(TAG, "getElement(" + std::to_string(i) +  "), Out of range in array for '" + this->getPlaceInFile().getLine() + "'");
    }
    std::vector<WsjcppYamlItem *>::iterator it;
    for (it = m_vObjects.begin(); it != m_vObjects.end(); ++it) {
        if (*it == pItem) {
            delete pItem;
            m_vObjects.erase(it);
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppYamlItem::isValue() {
    return m_nItemType == WSJCPP_YAML_ITEM_VALUE;
}

// ---------------------------------------------------------------------

std::string  WsjcppYamlItem::getValue() {
    if (m_nItemType != WSJCPP_YAML_ITEM_VALUE) {
        WsjcppLog::throw_err(TAG, "getValue, Element must be value for " + this->getForLogFormat());
    }
    return m_sValue;
}

// ---------------------------------------------------------------------

void WsjcppYamlItem::setValue(const std::string &sValue, WsjcppYamlQuotes nQuotes) {
    if (m_nItemType != WSJCPP_YAML_ITEM_VALUE) {
        WsjcppLog::throw_err(TAG, "setValue, Element must be value for " + this->getForLogFormat());
    }
    m_nValueQuotes = nQuotes;
    m_sValue = sValue;
}

// ---------------------------------------------------------------------

WsjcppYamlQuotes WsjcppYamlItem::getValueQuotes() {
    return m_nValueQuotes;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlItem::toString(std::string sIntent) {
    std::string sRet = "";
    if (this->isValue()) {
        if (m_nValueQuotes == WSJCPP_YAML_QUOTES_DOUBLE) {
            sRet = "\"" + m_sValue + "\"";
        } else if (m_nValueQuotes == WSJCPP_YAML_QUOTES_SINGLE) {
            sRet = "\'" + m_sValue + "\'";
        } else {
            sRet = m_sValue;
        }
        if (m_sComment.length() > 0) {
            if (sRet.length() > 0) {
                sRet += " ";
            }
            sRet += "# " + m_sComment;
        }
    } else if (this->isUndefined()) {
        for (int i = 0; i < m_vObjects.size(); i++) {
            if (m_vObjects[i]->isEmpty()) {
                sRet += "\n";
            } else {
                WsjcppLog::warn(TAG, "Undefined element conatins something else");
            }
            // sRet += std::to_string(m_vObjects.size());
        }
        return sRet;
    } else if (this->isEmpty()) {
        if (m_sComment.length() > 0) {
            sRet += sIntent + "# " + m_sComment;
        }
        // sRet += "\n";
        return sRet;
    } else if (this->isArray()) {
        for (int i = 0; i < m_vObjects.size(); i++) {
            WsjcppYamlItem *pItem = m_vObjects[i];
            if (pItem->isEmpty()) {
                sRet += pItem->toString(sIntent) + "\n";
                // sRet += "\n";
            } else if (pItem->isMap()) {
                std::string s = pItem->toString(sIntent + "  ");
                WsjcppCore::trim(s);
                sRet += sIntent + "- " + s;
                sRet += "\n";
            } else {
                sRet += sIntent + "- " + pItem->toString();
                sRet += "\n";
            }
        }
    } else if (this->isMap()) {
        for (int i = 0; i < m_vObjects.size(); i++) {
            WsjcppYamlItem *pItem = m_vObjects[i];
            if (pItem->isEmpty() ) {
                sRet += pItem->toString(sIntent);
                sRet += "\n";
            } else if (pItem->isArray() || pItem->isMap()) {
                if (pItem->getNameQuotes() == WSJCPP_YAML_QUOTES_DOUBLE) {
                    sRet += sIntent + "\"" + pItem->getName() + "\":";
                } else if (pItem->getNameQuotes() == WSJCPP_YAML_QUOTES_SINGLE) {
                    sRet += sIntent + "\'" + pItem->getName() + "\':";
                } else {
                    sRet += sIntent + pItem->getName() + ":";
                }
                if (pItem->getComment().length() > 0) {
                    sRet += " # " + pItem->getComment(); 
                }
                sRet += "\n";
                sRet += pItem->toString(sIntent + "  ");
            } else {
                std::string sVal = pItem->toString();
                std::string sVal_ = sVal;
                sVal_ = WsjcppCore::trim(sVal_);
                if (sVal_.length() > 0) {
                    sVal = " " + sVal;
                }
                if (pItem->getNameQuotes() == WSJCPP_YAML_QUOTES_DOUBLE) {
                    sRet += sIntent + "\"" + pItem->getName() + "\":" + sVal;
                } else if (pItem->getNameQuotes() == WSJCPP_YAML_QUOTES_SINGLE) {
                    sRet += sIntent + "\'" + pItem->getName() + "\':" + sVal;
                } else {
                    sRet += sIntent + pItem->getName() + ":" + sVal;
                }
                sRet += "\n";
            }
        }
    } else {
        sRet = ""; // undefined element must be empty
    }
    if (sIntent == "") {
        WsjcppCore::trim(sRet);
    }
    return sRet;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlItem::getItemTypeAsString() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        return "undefined";
    } else if (m_nItemType == WSJCPP_YAML_ITEM_ARRAY) {
        return "array";
    } else if (m_nItemType == WSJCPP_YAML_ITEM_MAP) {
        return "map";
    } else if (m_nItemType == WSJCPP_YAML_ITEM_VALUE) {
        return "value";
    }
    return "unknown";
}

// ---------------------------------------------------------------------

std::string WsjcppYamlItem::getForLogFormat() {
    return m_placeInFile.getForLogFormat();
}

// ---------------------------------------------------------------------

WsjcppYamlParsebleLine::WsjcppYamlParsebleLine(int nLine) {
    TAG = "WsjcppYamlParsebleLine(line:" + std::to_string(nLine) + ")";
    m_nLineNumber = nLine;
    m_sPrefix = "";
    m_bArrayItem = false;
    m_sComment = "";
    m_sTagName = "";
    m_sValue = "";
    m_nNameQuotes = WSJCPP_YAML_QUOTES_NONE;
    m_nValueQuotes = WSJCPP_YAML_QUOTES_NONE;
    m_bHasComment = false;
    m_bEmptyLine = false;
}

// ---------------------------------------------------------------------

WsjcppYamlParsebleLine::WsjcppYamlParsebleLine() 
: WsjcppYamlParsebleLine(-1) {

}

// ---------------------------------------------------------------------

int WsjcppYamlParsebleLine::getLineNumber() {
    return m_nLineNumber;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlParsebleLine::getPrefix() {
    return m_sPrefix;
}

// ---------------------------------------------------------------------

int WsjcppYamlParsebleLine::getIntent() {
    return m_sPrefix.length();
}

// ---------------------------------------------------------------------

bool WsjcppYamlParsebleLine::isArrayItem() {
    return m_bArrayItem;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlParsebleLine::getComment() {
    return m_sComment;
}

// ---------------------------------------------------------------------

bool WsjcppYamlParsebleLine::hasComment() {
    return m_bHasComment;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlParsebleLine::getName() {
    return m_sTagName;
}

// ---------------------------------------------------------------------

WsjcppYamlQuotes WsjcppYamlParsebleLine::getNameQuotes() {
    return m_nNameQuotes;
}

// ---------------------------------------------------------------------

bool WsjcppYamlParsebleLine::isEmptyName() {
    return m_sTagName.length() == 0;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlParsebleLine::getValue() {
    return m_sValue;
}

// ---------------------------------------------------------------------

WsjcppYamlQuotes WsjcppYamlParsebleLine::getValueQuotes() {
    return m_nValueQuotes;
}

// ---------------------------------------------------------------------

bool WsjcppYamlParsebleLine::isEmptyValue() {
    return m_sValue.length() == 0;
}

// ---------------------------------------------------------------------

bool WsjcppYamlParsebleLine::isEmptyLine() {
    return m_bEmptyLine;
}

// ---------------------------------------------------------------------

enum WsjcppYamlParserLineStates {
    WSJCPP_YAML_PARSER_LINE_STATE_NO,
    WSJCPP_YAML_PARSER_LINE_STATE_VALUE,
    WSJCPP_YAML_PARSER_LINE_STATE_COMMENT,
    WSJCPP_YAML_PARSER_LINE_STATE_STRING_DOUBLE_QUOTES,
    WSJCPP_YAML_PARSER_LINE_STATE_STRING_SINGLE_QUOTES,
    WSJCPP_YAML_PARSER_LINE_STATE_ESCAPING_DOUBLE_QUOTES,
    WSJCPP_YAML_PARSER_LINE_STATE_ESCAPING_SINGLE_QUOTES
};

bool WsjcppYamlParsebleLine::parseLine(const std::string &sLine, std::string &sError) {
    // reset variables
    m_bArrayItem = false;
    m_sPrefix = "";
    m_sComment = "";
    m_sTagName = "";
    m_sValue = "";
    m_bHasComment = false;
    m_nNameQuotes = WSJCPP_YAML_QUOTES_NONE;
    m_nValueQuotes = WSJCPP_YAML_QUOTES_NONE;
    m_bEmptyLine = false;
    std::string sLineTrim = sLine;
    sLineTrim = WsjcppCore::trim(sLineTrim);
    if (sLineTrim.length() == 0) {
        m_bEmptyLine = true;
        return true;
    }

    WsjcppYamlParserLineStates state = WSJCPP_YAML_PARSER_LINE_STATE_NO;
    for (int i = 0; i < sLine.length(); i++) {
        char c = sLine[i];
        if ((c == ' ' || c == '\t') && state == WSJCPP_YAML_PARSER_LINE_STATE_NO) {
            m_sPrefix += c;
        } else if (c == '#' && (state == WSJCPP_YAML_PARSER_LINE_STATE_NO || state == WSJCPP_YAML_PARSER_LINE_STATE_VALUE)) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_COMMENT;
            m_bHasComment = true;
        } else if (state == WSJCPP_YAML_PARSER_LINE_STATE_COMMENT) {
            if (c != '\r') {
                m_sComment += c;
            }
        } else if (c == '-' && state == WSJCPP_YAML_PARSER_LINE_STATE_NO) {
            m_bArrayItem = true;
            state = WSJCPP_YAML_PARSER_LINE_STATE_VALUE;
        } else if ((c != ' ' && c != '\t') && state == WSJCPP_YAML_PARSER_LINE_STATE_NO) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_VALUE;
            m_sValue += c;
            if (c == '"') {
                state = WSJCPP_YAML_PARSER_LINE_STATE_STRING_DOUBLE_QUOTES;
            }
            if (c == '\'') {
                state = WSJCPP_YAML_PARSER_LINE_STATE_STRING_SINGLE_QUOTES;
            }
        } else if (c == '"' && state == WSJCPP_YAML_PARSER_LINE_STATE_VALUE) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_STRING_DOUBLE_QUOTES;
            m_sValue += c;
        } else if (c == '\'' && state == WSJCPP_YAML_PARSER_LINE_STATE_VALUE) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_STRING_SINGLE_QUOTES;
            m_sValue += c;
        } else if (c == '\\' && state == WSJCPP_YAML_PARSER_LINE_STATE_STRING_DOUBLE_QUOTES) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_ESCAPING_DOUBLE_QUOTES;
            m_sValue += c;
        } else if (c == '\\' && state == WSJCPP_YAML_PARSER_LINE_STATE_STRING_SINGLE_QUOTES) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_ESCAPING_SINGLE_QUOTES;
            m_sValue += c;
        } else if (state == WSJCPP_YAML_PARSER_LINE_STATE_ESCAPING_DOUBLE_QUOTES) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_STRING_DOUBLE_QUOTES;
            m_sValue += c;
        } else if (state == WSJCPP_YAML_PARSER_LINE_STATE_ESCAPING_SINGLE_QUOTES) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_STRING_SINGLE_QUOTES;
            m_sValue += c;
        } else if (c == '"' && state == WSJCPP_YAML_PARSER_LINE_STATE_STRING_DOUBLE_QUOTES) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_VALUE;
            m_sValue += c;
        } else if (c == '\'' && state == WSJCPP_YAML_PARSER_LINE_STATE_STRING_SINGLE_QUOTES) {
            state = WSJCPP_YAML_PARSER_LINE_STATE_VALUE;
            m_sValue += c;
        } else if (c == ':' && state == WSJCPP_YAML_PARSER_LINE_STATE_VALUE) {
            if (m_sTagName.length() == 0 && this->canTagName(m_sValue)) {
                m_sTagName = m_sValue;
                m_sValue = ""; // reset value it was param name
            } else {
                m_sValue += c;
            }
        } else if (
            state == WSJCPP_YAML_PARSER_LINE_STATE_STRING_DOUBLE_QUOTES
            || state == WSJCPP_YAML_PARSER_LINE_STATE_STRING_SINGLE_QUOTES
        ) {
            m_sValue += c;
        } else if (state == WSJCPP_YAML_PARSER_LINE_STATE_VALUE) {
            m_sValue += c;
        } else {
            // skip
        }
    }

    if (
        state == WSJCPP_YAML_PARSER_LINE_STATE_STRING_DOUBLE_QUOTES
        || state == WSJCPP_YAML_PARSER_LINE_STATE_STRING_SINGLE_QUOTES
        || state == WSJCPP_YAML_PARSER_LINE_STATE_ESCAPING_DOUBLE_QUOTES
        || state == WSJCPP_YAML_PARSER_LINE_STATE_ESCAPING_SINGLE_QUOTES
    ) {
        sError = "Line has wrong format.";
        return false;
    }

    // split name and value
    /*for (int i = 0; i < m_sNameAndValue.size(); i++) {
        char c = m_sNameAndValue[i];
        if (c == ':' && m_sName.size() == 0) {
            m_sName = m_sValue;
            m_sValue = "";
        } else {
            m_sValue += c;
        }
    }*/
    
    m_sTagName = WsjcppCore::trim(m_sTagName);
    if (m_sTagName.length() > 0 && m_sTagName[0] == '"') {
        m_nNameQuotes = WSJCPP_YAML_QUOTES_DOUBLE;
        m_sTagName = removeStringDoubleQuotes(m_sTagName);
    }
    if (m_sTagName.length() > 0 && m_sTagName[0] == '\'') {
        m_nNameQuotes = WSJCPP_YAML_QUOTES_SINGLE;
        m_sTagName = removeStringSingleQuotes(m_sTagName);
    }

    m_sValue = WsjcppCore::trim(m_sValue);
    if (m_sValue.length() > 0 && m_sValue[0] == '"') {
        m_nValueQuotes = WSJCPP_YAML_QUOTES_DOUBLE;
        m_sValue = removeStringDoubleQuotes(m_sValue);
    }
    if (m_sValue.length() > 0 && m_sValue[0] == '\'') {
        m_nValueQuotes = WSJCPP_YAML_QUOTES_SINGLE;
        m_sValue = removeStringSingleQuotes(m_sValue);
    }

    m_sComment = WsjcppCore::trim(m_sComment);

    if (m_bArrayItem == false && m_sTagName.length() == 0 && m_sValue.length() > 0 ) {
        sError = "Value of name can be empty only for array-item (line: " + sLine + ")";
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppYamlParsebleLine::canTagName(const std::string &sVal) {
    std::string sTrim = sVal;
    sTrim = WsjcppCore::trim(sTrim);
    int nLen = sTrim.length();
    if (nLen == 0) {
        return false;
    }
    if (sTrim.length() > 0 && sTrim[0] == '"' && sTrim[nLen-1] == '"') {
        return true;
    }
    if (sTrim.length() > 0 && sTrim[0] == '\'' && sTrim[nLen-1] == '\'') {
        return true;
    }
    // check illegal char
    for (int i = 0; i < nLen; i++) {
        char c = sTrim[i];
        if (
            c != '-' && c != '_'
            && (c < '0' || c > '9')
            && (c < 'a' || c > 'z')
            && (c < 'A' || c > 'Z')
        ) {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlParsebleLine::removeStringDoubleQuotes(const std::string &sValue) {
    if (sValue.size() > 0 && sValue[0] != '"') {
        return sValue;
    }
    int nStartPos = 1;
    int nEndPos = sValue.size()-1;
    std::string sRet = "";
    bool bEscape = false;
    for (int i = nStartPos; i < nEndPos; i++) {
        char c = sValue[i];
        if (bEscape) {
            if (c == 'n') {
                sRet += '\n';
            } else if (c == 'r') {
                sRet += '\r';
            } else {
                sRet += c;
            }
        } else if (c == '\\') {
            bEscape = true;
        } else {
            sRet += c;
        }
    }
    return sRet;
}


// ---------------------------------------------------------------------

std::string WsjcppYamlParsebleLine::removeStringSingleQuotes(const std::string &sValue) {
    if (sValue.size() > 0 && sValue[0] != '\'') {
        return sValue;
    }
    int nStartPos = 1;
    int nEndPos = sValue.size()-1;
    std::string sRet = "";
    bool bEscape = false;
    for (int i = nStartPos; i < nEndPos; i++) {
        char c = sValue[i];
        if (bEscape) {
            if (c == 'n') {
                sRet += '\n';
            } else if (c == 'r') {
                sRet += '\r';
            } else {
                sRet += c;
            }
        } else if (c == '\\') {
            bEscape = true;
        } else {
            sRet += c;
        }
    }
    return sRet;
}

// ---------------------------------------------------------------------
// WsjcppYamlParserStatus

void WsjcppYamlParserStatus::logUnknownLine(const std::string &sPrefix) {
    WsjcppLog::warn(sPrefix, "\n"
        "  error:\n"
        "    desc: \"unknown_line\"\n"
        "    line_number: " + std::to_string(pCurItem->getPlaceInFile().getNumberOfLine()) + "\n"
        "    line: \"" + placeInFile.getLine() + "\"\n"
        "    intent: " + std::to_string(nIntent) +  "\n"
        "    filename: \"" + pCurItem->getPlaceInFile().getFilename() + "\""
    );
}

// ---------------------------------------------------------------------
// WsjcppYamlCursor

WsjcppYamlCursor::WsjcppYamlCursor(WsjcppYamlItem *pCurrentNode) {
    m_pCurrentNode = pCurrentNode;
    TAG = "WsjcppYamlCursor";
}

// ---------------------------------------------------------------------

WsjcppYamlCursor::WsjcppYamlCursor() 
: WsjcppYamlCursor(nullptr) {
    // nothing
}

// ---------------------------------------------------------------------

WsjcppYamlCursor::~WsjcppYamlCursor() {
    // do nothing
}

// ---------------------------------------------------------------------

bool WsjcppYamlCursor::isNull() const {
    return m_pCurrentNode == nullptr;
}

// ---------------------------------------------------------------------

bool WsjcppYamlCursor::isUndefined() const {
    return m_pCurrentNode != nullptr && m_pCurrentNode->isUndefined();
}

// ---------------------------------------------------------------------

bool WsjcppYamlCursor::isValue() const {
    return m_pCurrentNode != nullptr && m_pCurrentNode->isValue();
}

// ---------------------------------------------------------------------

bool WsjcppYamlCursor::isArray() const {
    return m_pCurrentNode != nullptr && m_pCurrentNode->isArray();
}

// ---------------------------------------------------------------------

size_t WsjcppYamlCursor::size() const {
    return m_pCurrentNode != nullptr && m_pCurrentNode->isArray() ? m_pCurrentNode->getLength() : -1;
}

// ---------------------------------------------------------------------

bool WsjcppYamlCursor::isMap() const {
    return m_pCurrentNode != nullptr && m_pCurrentNode->isMap();
}

// ---------------------------------------------------------------------

std::vector<std::string> WsjcppYamlCursor::keys() const {
    return m_pCurrentNode != nullptr && m_pCurrentNode->isMap() ? m_pCurrentNode->getKeys() : std::vector<std::string>();
}

// ---------------------------------------------------------------------

bool WsjcppYamlCursor::hasKey(const std::string &sKey) const {
    return m_pCurrentNode != nullptr && m_pCurrentNode->isMap() && m_pCurrentNode->hasElement(sKey);
}

// ---------------------------------------------------------------------

// WsjcppYamlCursor &WsjcppYamlCursor::set(const std::string &sName, const std::string &sValue) {
//     return *this;
// }
// 
// // ---------------------------------------------------------------------
// 
// WsjcppYamlCursor &WsjcppYamlCursor::set(const std::string &sName, int nValue) {
//     return *this;
// }
// 
// // ---------------------------------------------------------------------
// 
// WsjcppYamlCursor &WsjcppYamlCursor::set(const std::string &sName, bool bValue) {
//     return *this;
// }
// 
// // ---------------------------------------------------------------------
// 
// WsjcppYamlCursor &WsjcppYamlCursor::remove(const std::string &sKey) {
//     return *this;
// }

// ---------------------------------------------------------------------

std::string WsjcppYamlCursor::comment() {
    return m_pCurrentNode != nullptr ? m_pCurrentNode->getComment() : "";
}

// ---------------------------------------------------------------------

WsjcppYamlCursor &WsjcppYamlCursor::comment(const std::string& sComment) {
    if (m_pCurrentNode != nullptr) {
        m_pCurrentNode->setComment(sComment);
    }
    return *this;
}

// ---------------------------------------------------------------------

std::string WsjcppYamlCursor::valStr() {
    return m_pCurrentNode != nullptr ? m_pCurrentNode->getValue() : "";
}

// ---------------------------------------------------------------------

WsjcppYamlCursor &WsjcppYamlCursor::val(const std::string &sValue) {
    if (m_pCurrentNode != nullptr) {
        m_pCurrentNode->setValue(sValue); // TODO reserch need or not add quotes
    }
    return *this;
}

// ---------------------------------------------------------------------

WsjcppYamlCursor &WsjcppYamlCursor::val(const char *sValue) {
    this->val(std::string(sValue));
    return *this;
}

// ---------------------------------------------------------------------

int WsjcppYamlCursor::valInt() {
    if (m_pCurrentNode != nullptr) {
        std::string sValue = m_pCurrentNode->getValue();
        sValue = WsjcppCore::toLower(sValue);
        int nValue = std::atoi(sValue.c_str());
        if (std::to_string(nValue) != sValue) {
            WsjcppLog::throw_err(TAG, "valInt, Element must be int but have a string" + m_pCurrentNode->getForLogFormat());
        }
        return nValue;
    }
    return 0;
}

// ---------------------------------------------------------------------

WsjcppYamlCursor &WsjcppYamlCursor::val(int nValue) {
    if (m_pCurrentNode != nullptr) {
        m_pCurrentNode->setValue(std::to_string(nValue));
    }
    return *this;
}

// ---------------------------------------------------------------------

bool WsjcppYamlCursor::valBool() {
    if (m_pCurrentNode != nullptr) {
        std::string sValue = m_pCurrentNode->getValue();
        sValue = WsjcppCore::toLower(sValue);
        if (sValue == "yes" || sValue == "true") {
            return true;
        } else if (sValue == "no" || sValue == "false") {
            return false;
        } else {
            WsjcppLog::throw_err(TAG, "valBool, Element must be bool expected with ignore case like"
                "['yes','no','true','false']  for " + m_pCurrentNode->getForLogFormat());
        }
    }
    return false;
}

// ---------------------------------------------------------------------

WsjcppYamlCursor &WsjcppYamlCursor::val(bool bValue) {
    if (m_pCurrentNode != nullptr) {
        m_pCurrentNode->setValue((bValue ? "yes" : "no"));
    }
    return *this;
}

// ---------------------------------------------------------------------

WsjcppYamlCursor WsjcppYamlCursor::operator[](int idx) const {
    if (m_pCurrentNode != nullptr && m_pCurrentNode->isArray() && idx < m_pCurrentNode->getLength() && idx >= 0) {
        return WsjcppYamlCursor(m_pCurrentNode->getElement(idx));
    }
    return WsjcppYamlCursor();
}

// ---------------------------------------------------------------------

WsjcppYamlCursor WsjcppYamlCursor::operator[](const std::string &sName) const {
    if (m_pCurrentNode != nullptr && m_pCurrentNode->isMap() && m_pCurrentNode->hasElement(sName)) {
        return WsjcppYamlCursor(m_pCurrentNode->getElement(sName));
    }
    return WsjcppYamlCursor();
}

// ---------------------------------------------------------------------
// WsjcppYaml

WsjcppYaml::WsjcppYaml() {
    m_pRoot = nullptr;
    TAG = "WsjcppYaml";
}

// ---------------------------------------------------------------------

WsjcppYaml::~WsjcppYaml() {
    delete m_pRoot;
}

// ---------------------------------------------------------------------

void WsjcppYaml::clear() {
    delete m_pRoot;
    m_pRoot = nullptr;
}

// ---------------------------------------------------------------------

bool WsjcppYaml::loadFromFile(const std::string &sFileName, std::string &sError) {
    std::string sTextContent;
    if (!WsjcppCore::readTextFile(sFileName, sTextContent)) {
        return false;    
    }
    return parse(sFileName, sTextContent, sError);
}

// ---------------------------------------------------------------------

bool WsjcppYaml::saveToFile(const std::string &sFileName) {
    std::string sBuffer = m_pRoot->toString();
    if (!WsjcppCore::writeFile(sFileName, sBuffer)) {
        return false;    
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppYaml::loadFromString(const std::string &sBufferName, const std::string &sBuffer, std::string &sError) {
    return parse(sBufferName, sBuffer, sError);
}

// ---------------------------------------------------------------------

bool WsjcppYaml::saveToString(std::string &sBuffer) { // TODO move to WsjcppCore
    sBuffer = m_pRoot->toString();
    return true;
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppYaml::getRoot() {
    return m_pRoot;
}

// ---------------------------------------------------------------------

WsjcppYamlCursor WsjcppYaml::getCursor() const {
    return WsjcppYamlCursor(m_pRoot);
}

// ---------------------------------------------------------------------

WsjcppYamlCursor WsjcppYaml::operator[](int idx) const {
     return this->getCursor()[idx];
}

// ---------------------------------------------------------------------

WsjcppYamlCursor WsjcppYaml::operator[](const std::string &sName) const {
    return this->getCursor()[sName];
}

// ---------------------------------------------------------------------

std::vector<std::string> WsjcppYaml::splitToLines(const std::string &sBuffer) {
    std::vector<std::string> vLines;
    std::string sLine = "";
    int nSize = sBuffer.length();
    for (int i = 0; i < nSize; i++) {
        char c = sBuffer[i];
        if (c == '\n') {
            vLines.push_back(sLine);
            sLine = "";
        } else {
            sLine += c;
        }
    }
    if (sLine.length() > 0) {
        vLines.push_back(sLine);
    }
    return vLines;
}

// ---------------------------------------------------------------------

bool WsjcppYaml::parse(const std::string &sFileName, const std::string &sBuffer, std::string &sError) {
    this->clear();
    if (m_pRoot == nullptr) {
        m_pRoot = new WsjcppYamlItem(nullptr, WsjcppYamlPlaceInFile(), WSJCPP_YAML_ITEM_MAP);
    }

    std::vector<std::string> vLines = this->splitToLines(sBuffer);
    WsjcppYamlParserStatus st;
    st.pCurItem = m_pRoot; // TODO recreate again new root element
    st.placeInFile.setFilename(sFileName);
    st.nIntent = 0;
    m_pRoot->setPlaceInFile(st.placeInFile);

    for (int nLine = 0; nLine < vLines.size(); nLine++) {
        st.placeInFile.setLine(vLines[nLine]);
        // WsjcppLog::info(TAG, "Line(" + std::to_string(nLine) + ") '" + st.sLine + "'");
        st.placeInFile.setNumberOfLine(nLine);
        st.line = WsjcppYamlParsebleLine(nLine);
        if (!st.line.parseLine(st.placeInFile.getLine(), sError)) {
            return false;
        }
        
        bool isEmptyName = st.line.isEmptyName();
        bool isEmptyValue = st.line.isEmptyValue();
        bool isArrayItem = st.line.isArrayItem();
        int nLineIntent = st.line.getIntent();
        int nDiffIntent = nLineIntent - st.nIntent;
        
        if (st.line.isEmptyLine()) {
            
            
            if (st.pCurItem != nullptr) {
                
                if (st.pCurItem->isArray() || st.pCurItem->isMap() || st.pCurItem->isUndefined()) {
                    WsjcppYamlItem *pItem = new WsjcppYamlItem(
                        st.pCurItem, st.placeInFile,
                        WsjcppYamlItemType::WSJCPP_YAML_ITEM_EMPTY
                    );
                    st.pCurItem->appendElement(pItem);
                } else if (st.pCurItem->getParent() != nullptr && (st.pCurItem->getParent()->isArray() || st.pCurItem->getParent()->isMap())) {
                    WsjcppYamlItem *pItem = new WsjcppYamlItem(
                        st.pCurItem->getParent(), st.placeInFile,
                        WsjcppYamlItemType::WSJCPP_YAML_ITEM_EMPTY
                    );
                    st.pCurItem->getParent()->appendElement(pItem);
                } else {
                    WsjcppLog::throw_err(TAG, "Empty element can be added only to map or to array");
                }
            }
            continue;
        }

        while (nDiffIntent < 0) {
            st.pCurItem = st.pCurItem->getParent();
            st.nIntent = st.nIntent - 2;
            nDiffIntent = nLineIntent - st.nIntent;
            if (st.pCurItem == nullptr) {
                sError = "Current item is nullptr";
                return false;
            }
        }

        if (nDiffIntent == 0) {
            if (st.line.isEmptyName()) {
                if ( ! isEmptyValue && isArrayItem) {
                    process_sameIntent_emptyName_hasValue_arrayItem(st);
                } else if (! isEmptyValue && ! isArrayItem) {
                    process_sameIntent_emptyName_hasValue_noArrayItem(st);
                } else if (isEmptyValue && isArrayItem) {
                    process_sameIntent_emptyName_emptyValue_arrayItem(st);
                } else if (isEmptyValue && ! isArrayItem) {
                    process_sameIntent_emptyName_emptyValue_noArrayItem(st);
                } else {
                    st.logUnknownLine(TAG);
                }
            } else if ( ! st.line.isEmptyName()) {
                if ( ! isEmptyValue && isArrayItem) {
                    process_sameIntent_hasName_hasValue_arrayItem(st);
                } else if ( ! isEmptyValue && ! isArrayItem) {
                    process_sameIntent_hasName_hasValue_noArrayItem(st);
                } else if (isEmptyValue && isArrayItem) {
                    process_sameIntent_hasName_emptyValue_arrayItem(st);
                } else if (isEmptyValue && ! isArrayItem) {
                    process_sameIntent_hasName_emptyValue_noArrayItem(st);
                } else {
                    st.logUnknownLine(TAG);
                }
            } else {
                st.logUnknownLine(TAG);
            }
        } else {
            st.logUnknownLine(TAG);
        }
    }
    return true;
}

// ---------------------------------------------------------------------

void WsjcppYaml::process_sameIntent_hasName_emptyValue_arrayItem(WsjcppYamlParserStatus &st) {
    st.logUnknownLine("process_sameIntent_hasName_emptyValue_arrayItem");
}

// ---------------------------------------------------------------------

void WsjcppYaml::process_sameIntent_hasName_emptyValue_noArrayItem(WsjcppYamlParserStatus &st) {
    WsjcppYamlItem *pItem = new WsjcppYamlItem(
        st.pCurItem, st.placeInFile, 
        WsjcppYamlItemType::WSJCPP_YAML_ITEM_UNDEFINED
    );
    if (st.line.getValueQuotes() != WSJCPP_YAML_QUOTES_NONE) {
        pItem->doValue();
        pItem->setValue(st.line.getValue(), st.line.getValueQuotes());
    }
    pItem->setName(st.line.getName(), st.line.getNameQuotes());
    pItem->setComment(st.line.getComment());
    st.pCurItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WsjcppYaml::process_sameIntent_hasName_hasValue_arrayItem(WsjcppYamlParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WsjcppYamlItem *pMapItem = new WsjcppYamlItem(
        st.pCurItem, st.placeInFile, 
        WsjcppYamlItemType::WSJCPP_YAML_ITEM_MAP
    );
    st.pCurItem->appendElement(pMapItem);
    st.pCurItem = pMapItem;
    st.nIntent = st.nIntent + 2;

    WsjcppYamlItem *pItem = new WsjcppYamlItem(
        st.pCurItem, st.placeInFile, 
        WsjcppYamlItemType::WSJCPP_YAML_ITEM_VALUE
    );
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue(), st.line.getValueQuotes());
    pItem->setName(st.line.getName(), st.line.getNameQuotes());
    pMapItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WsjcppYaml::process_sameIntent_hasName_hasValue_noArrayItem(WsjcppYamlParserStatus &st) {
    WsjcppYamlItem *pItem = new WsjcppYamlItem(
        st.pCurItem, st.placeInFile, 
        WsjcppYamlItemType::WSJCPP_YAML_ITEM_VALUE
    );
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue(), st.line.getValueQuotes());
    pItem->setName(st.line.getName(), st.line.getNameQuotes());
    st.pCurItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WsjcppYaml::process_sameIntent_emptyName_hasValue_arrayItem(WsjcppYamlParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WsjcppYamlItem *pItem = new WsjcppYamlItem(
        st.pCurItem, st.placeInFile,
        WsjcppYamlItemType::WSJCPP_YAML_ITEM_VALUE
    );
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue(), st.line.getValueQuotes());
    st.pCurItem->appendElement(pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WsjcppYaml::process_sameIntent_emptyName_hasValue_noArrayItem(WsjcppYamlParserStatus &st) {
    st.logUnknownLine("TODO process_sameIntent_emptyName_hasValue_noArrayItem");
}

// ---------------------------------------------------------------------

void WsjcppYaml::process_sameIntent_emptyName_emptyValue_arrayItem(WsjcppYamlParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WsjcppYamlItem *pItem = new WsjcppYamlItem(
        st.pCurItem, st.placeInFile, 
        WsjcppYamlItemType::WSJCPP_YAML_ITEM_VALUE
    );
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue(), st.line.getValueQuotes());
    st.pCurItem->appendElement(pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WsjcppYaml::process_sameIntent_emptyName_emptyValue_noArrayItem(WsjcppYamlParserStatus &st) {
    WsjcppYamlItem *pItem = new WsjcppYamlItem(
        st.pCurItem, st.placeInFile,
        WsjcppYamlItemType::WSJCPP_YAML_ITEM_EMPTY
    );
    pItem->setComment(st.line.getComment());
    st.pCurItem->appendElement(pItem);
}

// ---------------------------------------------------------------------

