/*
MIT License

Copyright (c) 2019-2025 wsjcpp

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Official Source Code: https://github.com/wsjcpp/wsjcpp-yaml
*/

#include <iostream>
#include <wsjcpp_yaml.h>

int main() {
    WsjcppYaml yml;
    yml.getRoot()->setElementValue("p1", "val1");
    yml.getRoot()->createElementMap("some");
    WsjcppYamlNode *pSome = yml.getRoot()->getElement("some");
    pSome->setElementValue("p2", "val2");
    pSome->createElementMap("sub-some");
    WsjcppYamlNode *pSubSome = pSome->getElement("sub-some");
    pSubSome->setElementValue("p3", "val3");
    pSome->createElementArray("arr-some");
    WsjcppYamlNode *pArrSome = pSome->getElement("arr-some");
    pArrSome->setComment("some array here");
    pArrSome->appendElementValue("1234");
    WsjcppYamlPlaceInFile placeInFile;
    WsjcppYamlNode *pItemMap = new WsjcppYamlNode(pArrSome, &yml, placeInFile, WSJCPP_YAML_NODE_MAP);
    pItemMap->setComment("some comment for a map"); // why not work ????
    pArrSome->appendElement(pItemMap);
    pItemMap->setElementValue("p4", "val4");
    pItemMap->setElementValue("p5", "val5");
    yml.getRoot()->setElementValue("p6", "val6");

    int ret = 0;

    std::string sExpectedYaml = ""
        "p1: val1\n"
        "some:\n"
        "  p2: val2\n"
        "  sub-some:\n"
        "    p3: val3\n"
        "  arr-some: # some array here\n"
        "    - 1234\n"
        "    - p4: val4\n"
        "      p5: val5\n"
        "p6: val6";

    std::string sSaved = yml.getRoot()->toString();

    if (sSaved != sExpectedYaml) {
        std::cerr << "ERROR (1). Not equal. Expected: \n---\n" << sExpectedYaml << "\n---\n, but got \n---\n" << sSaved << "\n---\n" << std::endl;
        ret = -1;
    }

    std::string sError = "";
    std::string sSaved2 = "";
    std::string sExpectedYaml2 = sExpectedYaml + "\n";
    if (!yml.saveToString(sSaved2, sError)) {
        std::cerr << "Error save: " << sError << std::endl;
        return -1;
    }

    if (sSaved2 != sExpectedYaml2) {
        std::cerr << "ERROR (2). Not equal. Expected: \n---\n" << sExpectedYaml2 << "\n---\n, but got \n---\n" << sSaved2 << "\n---\n" << std::endl;
        ret = -1;
    }

    return ret;
}