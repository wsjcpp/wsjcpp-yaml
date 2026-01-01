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

    std::string sInput =
        "some: \n"
        "  - n1: 1\n"
        "    n2: 2\n"
        "\n"
        "some2: r \n"
    ;

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromString("test_append_element_issue_30.yml", sInput, sError)) {
        std::cerr << sError << std::endl;
        return -1;
    }

    WsjcppYamlNode *pSome = yaml.getRoot()->getElement("some");
    WsjcppYamlNode *pSome0 = pSome->getElement(0);
    pSome0->setElementValue("n3", "3");

    // WsjcppYamlNode *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
    WsjcppYamlPlaceInFile placeInFile;

    WsjcppYamlNode *pItemMap = new WsjcppYamlNode(pSome, &yaml, placeInFile, WSJCPP_YAML_NODE_MAP);
    pSome->appendElement(pItemMap);
    pItemMap->setElementValue("p4", "val4");
    pItemMap->setElementValue("p5", "val5");

    std::string sExpectedYaml =
        "some:\n"
        "  - n1: 1\n"
        "    n2: 2\n"
        "    n3: 3\n"
        "  - p4: val4\n"
        "    p5: val5\n"
        "\n"
        "some2: r"
    ;

    std::string sSaved = yaml.getRoot()->toString();

    if (sSaved != sExpectedYaml) {
        std::cerr << "ERROR (1). Not equal. Expected: \n---\n" << sExpectedYaml << "\n---\n, but got \n---\n" << sSaved << "\n---\n" << std::endl;
        return -1;
    }

    return 0;
}