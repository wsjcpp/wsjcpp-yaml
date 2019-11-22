
#include "wsjcpp_yaml.h"
#include <fallen.h>

// ---------------------------------------------------------------------
// WSJCppYAMLItem

WSJCppYAMLItem::WSJCppYAMLItem(
    WSJCppYAMLItem *pParent, 
    int nOriginalNumberOfLine, 
    const std::string &sOriginalLine,
    WSJCppYAMLItemType nItemType
) {
    m_pParent = pParent;
    m_nOriginalNumberOfLine = nOriginalNumberOfLine;
    m_sOriginalLine = sOriginalLine;
    m_nItemType = nItemType;
    TAG = "WSJCppYAMLItem(line:" + std::to_string(m_nOriginalNumberOfLine) + ":'" + sOriginalLine + "')";
}

// ---------------------------------------------------------------------

WSJCppYAMLItem::~WSJCppYAMLItem() {
    for (int i = 0; i < m_vObjects.size(); i++) {
        WSJCppYAMLItem *pItem = m_vObjects[i];
        delete pItem;
    }
    m_vObjects.clear();
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppYAMLItem::getParent() {
    return m_pParent;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::getOriginalLine() {
    return m_sOriginalLine;
}

int WSJCppYAMLItem::getOriginalNumberOfLine() {
    return m_nOriginalNumberOfLine;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::setComment(const std::string &sComment) {
    m_sComment = sComment;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::getComment() {
    return m_sComment;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::setName(const std::string &sName) {
    m_sName = sName;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isEmpty() {
    return m_nItemType == WSJCPP_YAML_ITEM_EMPTY;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::doEmpty() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_EMPTY;
    } else {
        Log::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isUndefined() {
    return m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::doArray() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_ARRAY;
    } else {
        Log::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::doMap() {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_MAP;
    } else {
        Log::throw_err(TAG, "Element already defined as '" + this->getItemTypeAsString() + "'");
    }
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isMap() {
    return m_nItemType == WSJCPP_YAML_ITEM_MAP;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::hasElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        Log::throw_err(TAG, "hasElement('" + sName + "'): Element must be map");
    }
    for (int i = 0; i < m_vObjects.size(); i++) {
        if (m_vObjects[i]->getName() == sName) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppYAMLItem::getElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        Log::throw_err(TAG, "getElement: Element must be map");
    }
    
    for (int i = 0; i < m_vObjects.size(); i++) {
        if (m_vObjects[i]->getName() == sName) {
            return m_vObjects[i];
        }
    }
    Log::throw_err(TAG, "Element '" + sName + "' not found");    
    return nullptr;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::setElement(const std::string &sName, WSJCppYAMLItem *pItem) {
    if (m_nItemType == WSJCPP_YAML_ITEM_UNDEFINED) {
        m_nItemType = WSJCPP_YAML_ITEM_MAP; // change item type to map on first element  
    }

    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        Log::throw_err(TAG, "setElement, Element must be 'map' for line(" + std::to_string(pItem->getOriginalNumberOfLine()) + "): '" + pItem->getOriginalLine() + "'");
    }
    
    if (this->hasElement(sName)) { // TODO remove previous element
        Log::throw_err(TAG, "setElement: Map already has element with this name: '" + sName + "'");
    }
    m_vObjects.push_back(pItem); // TODO create clone
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::removeElement(const std::string &sName) {
    if (m_nItemType != WSJCPP_YAML_ITEM_MAP) {
        Log::throw_err(TAG, "removeElement: Element must be map");
    }
    // TODO erase
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isArray() {
    return m_nItemType == WSJCPP_YAML_ITEM_ARRAY;
}

// ---------------------------------------------------------------------

int WSJCppYAMLItem::getLength() {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        Log::throw_err(TAG, "getLength, Element must be array");
    }
    return m_vObjects.size();
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppYAMLItem::getElement(int i) {
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        Log::throw_err(TAG, "getElement, Element must be array");
    }
    if( i > m_vObjects.size()-1) {
        Log::throw_err(TAG, "getElement, Out of range in array");
    }
    return m_vObjects[i];
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::appendElement(WSJCppYAMLItem *pItem) {
    if (pItem->isEmpty()) {
        m_vObjects.push_back(pItem); // TODO clone object
        return true;
    }
    if (m_nItemType != WSJCPP_YAML_ITEM_ARRAY) {
        Log::throw_err(TAG, "appendElement, Element must be array for line(" + std::to_string(pItem->getOriginalNumberOfLine()) + "): '" + pItem->getOriginalLine() + "'");
    }
    m_vObjects.push_back(pItem); // TODO clone object
    return true;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLItem::isValue() {
    return m_nItemType == WSJCPP_YAML_ITEM_VALUE;
}

// ---------------------------------------------------------------------

std::string  WSJCppYAMLItem::getValue() {
    return m_sValue;
}

// ---------------------------------------------------------------------

void WSJCppYAMLItem::setValue(const std::string &sValue) {
    m_sValue = sValue;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::toString(std::string sIntent) {
    std::string sRet = "";
    if (this->isValue()) {
        sRet = m_sValue;
        if (m_sComment.length() > 0) {
            if (sRet.length() > 0) {
                sRet += " ";
            }
            sRet += "# " + m_sComment;
        }
    } else if (this->isEmpty()) {
        if (m_sComment.length() > 0) {
            sRet += "# " + m_sComment;
        }
    } else if (this->isArray()) {
        sRet += "\n";
        for (int i = 0; i < m_vObjects.size(); i++) {
            sRet += sIntent + "- " + m_vObjects[i]->toString();
            sRet += "\n";
        }
    } else if (this->isMap()) {
        for (int i = 0; i < m_vObjects.size(); i++) {
            WSJCppYAMLItem *pItem = m_vObjects[i];
            if (pItem->isEmpty() ) {
                sRet += pItem->toString(sIntent + "  ");
            } else if (pItem->isArray() || pItem->isMap()) {
                sRet += pItem->getName() + ":";
                if (pItem->getComment().length() > 0) {
                    sRet += " # " + pItem->getComment(); 
                }
                sRet += m_vObjects[i]->toString(sIntent + "  ");
            } else {
                sRet += m_vObjects[i]->getName() + ": " + m_vObjects[i]->toString();
            }
            sRet += "\n";
        }
    } else {
        sRet = "TODO: undefined";
    }
    if (sIntent == "") {
        Fallen::trim(sRet);
    }
    return sRet;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLItem::getItemTypeAsString() {
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

WSJCppYAMLParsebleLine::WSJCppYAMLParsebleLine(int nLine) {
    TAG = "WSJCppYAMLParsebleLine(line:" + std::to_string(nLine) + ")";
    m_nLine = nLine;
}

// ---------------------------------------------------------------------

WSJCppYAMLParsebleLine::WSJCppYAMLParsebleLine() 
: WSJCppYAMLParsebleLine(-1) {

}

// ---------------------------------------------------------------------

int WSJCppYAMLParsebleLine::getLineNumber() {
    return m_nLine;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::getPrefix() {
    return m_sPrefix;
}

// ---------------------------------------------------------------------

int WSJCppYAMLParsebleLine::getIntent() {
    return m_sPrefix.length();
}

// ---------------------------------------------------------------------

bool WSJCppYAMLParsebleLine::isArrayItem() {
    return m_bArrayItem;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::getComment() {
    return m_sComment;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLParsebleLine::isEmptyName() {
    return m_sName.length() == 0;
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::getValue() {
    return m_sValue;
}

// ---------------------------------------------------------------------

bool WSJCppYAMLParsebleLine::isEmptyValue() {
    return m_sValue.length() == 0;
}

// ---------------------------------------------------------------------

void WSJCppYAMLParsebleLine::parseLine(const std::string &sLine) {
    // reset variables
    m_bArrayItem = false;
    m_sPrefix = "";
    m_sComment = "";
    m_sNameAndValue = "";
    m_sName = "";
    m_sValue = "";
    m_bNameWasWithQuotes = false;
    m_bValueWasWithQuotes = false;

    WSJCppYAMLParserLineStates state = WSJCppYAMLParserLineStates::NO;
    for (int i = 0; i < sLine.length(); i++) {
        char c = sLine[i];
        if ((c == ' ' || c == '\t') && state == WSJCppYAMLParserLineStates::NO) {
            m_sPrefix += c;
        } else if (c == '#' && (state == WSJCppYAMLParserLineStates::NO || state == WSJCppYAMLParserLineStates::NAME_AND_VALUE)) {
            state = WSJCppYAMLParserLineStates::COMMENT;
        } else if (state == WSJCppYAMLParserLineStates::COMMENT) {
            if (c != '\r') {
                m_sComment += c;
            }
        } else if (c == '-' && state == WSJCppYAMLParserLineStates::NO) {
            m_bArrayItem = true;
            state = WSJCppYAMLParserLineStates::NAME_AND_VALUE;
        } else if ((c != ' ' && c != '\t') && state == WSJCppYAMLParserLineStates::NO) {
            state = WSJCppYAMLParserLineStates::NAME_AND_VALUE;
            m_sNameAndValue += c;
            if (c == '"') {
                state = WSJCppYAMLParserLineStates::STRING;
            }
        } else if (c == '"' && state == WSJCppYAMLParserLineStates::NAME_AND_VALUE) {
            state = WSJCppYAMLParserLineStates::STRING;
            m_sNameAndValue += c;
        } else if (c == '\\' && state == WSJCppYAMLParserLineStates::STRING) {
            state = WSJCppYAMLParserLineStates::ESCAPING;
            m_sNameAndValue += c;
        } else if (state == WSJCppYAMLParserLineStates::ESCAPING) {
            state = WSJCppYAMLParserLineStates::STRING;
            m_sNameAndValue += c;
        } else if (c == '"' && state == WSJCppYAMLParserLineStates::STRING) {
            state = WSJCppYAMLParserLineStates::NAME_AND_VALUE;
            m_sNameAndValue += c;
        } else if (state == WSJCppYAMLParserLineStates::STRING) {
            m_sNameAndValue += c;
        } else if (state == WSJCppYAMLParserLineStates::NAME_AND_VALUE) {
            m_sNameAndValue += c;
        } else {
            // skip
        }
    }

    if (state == WSJCppYAMLParserLineStates::STRING 
      || state == WSJCppYAMLParserLineStates::ESCAPING
    ) {
        Log::throw_err(TAG, "wrong format");
    }

    // split name and value
    for (int i = 0; i < m_sNameAndValue.size(); i++) {
        char c = m_sNameAndValue[i];
        if (c == ':' && m_sName.size() == 0) {
            m_sName = m_sValue;
            m_sValue = "";
        } else {
            m_sValue += c;
        }
    }
    
    Fallen::trim(m_sName);
    if (m_sName.length() > 0 && m_sName[0] == '"') {
        m_bNameWasWithQuotes = true;
        m_sName = removeStringDoubleQuotes(m_sName);
    }

    Fallen::trim(m_sValue);
    if (m_sValue.length() > 0 && m_sValue[0] == '"') {
        m_bValueWasWithQuotes = true;
        m_sValue = removeStringDoubleQuotes(m_sValue);
    }

    Fallen::trim(m_sComment);
}

// ---------------------------------------------------------------------

std::string WSJCppYAMLParsebleLine::removeStringDoubleQuotes(const std::string &sValue) {
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
// WSJCppYAMLParserStatus

void WSJCppYAMLParserStatus::logUnknownLine(const std::string &sPrefix) {
    Log::warn(sPrefix, "Unknown line (" + std::to_string(nLine) + "): '" + sLine + "' \n"
        + "Current Intent: " + std::to_string(nIntent) +  "\n"
        + "Current Item(line: " + std::to_string(pCurItem->getOriginalNumberOfLine()) + "): '" + pCurItem->getOriginalLine() + "'"
    );
}

// ---------------------------------------------------------------------
// WSJCppYAML

WSJCppYAML::WSJCppYAML() {
    m_pRoot = new WSJCppYAMLItem(nullptr, -1, "", WSJCPP_YAML_ITEM_MAP);
}

// ---------------------------------------------------------------------

WSJCppYAML::~WSJCppYAML() {
    delete m_pRoot;
}

// ---------------------------------------------------------------------

bool WSJCppYAML::loadFromFile(const std::string &sFileName) {
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppYAML::saveToFile(const std::string &sFileName) {
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppYAML::loadFromString(const std::string &sBuffer) {
    return false;
}

// ---------------------------------------------------------------------

bool WSJCppYAML::loadFromString(std::string &sBuffer) {
    return parse(sBuffer);
}

// ---------------------------------------------------------------------

bool WSJCppYAML::saveToString(std::string &sBuffer) { // TODO move to fallen
    sBuffer = m_pRoot->toString();
    return true;
}

// ---------------------------------------------------------------------

WSJCppYAMLItem *WSJCppYAML::getRoot() {
    return m_pRoot;
}

// ---------------------------------------------------------------------

std::vector<std::string> WSJCppYAML::splitToLines(const std::string &sBuffer) {
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

bool WSJCppYAML::parse(const std::string &sBuffer) {
    std::vector<std::string> vLines = this->splitToLines(sBuffer);
    WSJCppYAMLParserStatus st;
    st.pCurItem = m_pRoot; // TODO create again new root element
    st.nIntent = 0;

    for (int nLine = 0; nLine < vLines.size(); nLine++) {
        st.sLine = vLines[nLine];
        // Log::info(TAG, "Line(" + std::to_string(nLine) + ") '" + st.sLine + "'");
        st.nLine = nLine;
        st.line = WSJCppYAMLParsebleLine(nLine);
        st.line.parseLine(st.sLine);
        
        bool isEmptyName = st.line.isEmptyName();
        bool isEmptyValue = st.line.isEmptyValue();
        bool isArrayItem = st.line.isArrayItem();
        int nLineIntent = st.line.getIntent();
        int nDiffIntent = nLineIntent - st.nIntent;

        // TODO check comment
        /*if (isEmptyName && isEmptyValue && isArrayItem) {
            continue;
        }*/

        while (nDiffIntent < 0) {
            st.pCurItem = st.pCurItem->getParent();
            st.nIntent = st.nIntent - 2;
            nDiffIntent = nLineIntent - st.nIntent;
            if (st.pCurItem == nullptr) {
                Log::throw_err(TAG, "cur item is nullptr");
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
    return false;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_hasName_emptyValue_arrayItem(WSJCppYAMLParserStatus &st) {
    st.logUnknownLine("process_sameIntent_hasName_emptyValue_arrayItem");
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_hasName_emptyValue_noArrayItem(WSJCppYAMLParserStatus &st) {
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(
        st.pCurItem, 
        st.nLine, 
        st.sLine, 
        WSJCppYAMLItemType::WSJCPP_YAML_ITEM_UNDEFINED
    );
    pItem->setName(st.line.getName());
    pItem->setComment(st.line.getComment());
    st.pCurItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_hasName_hasValue_arrayItem(WSJCppYAMLParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WSJCppYAMLItem *pMapItem = new WSJCppYAMLItem(st.pCurItem, st.nLine, st.sLine, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_MAP);
    st.pCurItem->appendElement(pMapItem);
    st.pCurItem = pMapItem;
    st.nIntent = st.nIntent + 2;

    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(st.pCurItem, st.nLine, st.sLine, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue());
    pItem->setName(st.line.getName());
    pMapItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_hasName_hasValue_noArrayItem(WSJCppYAMLParserStatus &st) {
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(st.pCurItem, st.nLine, st.sLine, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue());
    pItem->setName(st.line.getName());
    st.pCurItem->setElement(st.line.getName(), pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_emptyName_hasValue_arrayItem(WSJCppYAMLParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(st.pCurItem, st.nLine, st.sLine, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue());
    st.pCurItem->appendElement(pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_emptyName_hasValue_noArrayItem(WSJCppYAMLParserStatus &st) {
    st.logUnknownLine("TODO process_sameIntent_emptyName_hasValue_noArrayItem");
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_emptyName_emptyValue_arrayItem(WSJCppYAMLParserStatus &st) {
    if (st.pCurItem->isUndefined()) {
        st.pCurItem->doArray();
    }
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(st.pCurItem, st.nLine, st.sLine, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_VALUE);
    pItem->setComment(st.line.getComment());
    pItem->setValue(st.line.getValue());
    st.pCurItem->appendElement(pItem);
    st.pCurItem = pItem;
    st.nIntent = st.nIntent + 2;
}

// ---------------------------------------------------------------------

void WSJCppYAML::process_sameIntent_emptyName_emptyValue_noArrayItem(WSJCppYAMLParserStatus &st) {
    WSJCppYAMLItem *pItem = new WSJCppYAMLItem(st.pCurItem, st.nLine, st.sLine, WSJCppYAMLItemType::WSJCPP_YAML_ITEM_EMPTY);
    pItem->setComment(st.line.getComment());
    st.pCurItem->appendElement(pItem);
}

// ---------------------------------------------------------------------