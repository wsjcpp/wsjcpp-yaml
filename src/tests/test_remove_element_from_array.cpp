#include <iostream>
#include <wsjcpp_yaml.h>

int main() {
    std::string sFilepath = "../../../../src/tests/data-tests/remove-element-from-array.yml";
    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromFile(sFilepath, sError)) {
        std::cerr << "Error parsing: " << sError << std::endl;
        return -1;
    }

    int ret = 0;

    WsjcppYamlNode *pArr1 = yaml.getRoot()->getElement("arr1");
    if (pArr1->getLength() != 4) {
        std::cerr << "Check failed: arr1 len" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(0)->getElement("name")->getValue() != "i1") {
        std::cerr << "Check failed: arr1 name0" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(1)->getElement("name")->getValue() != "i2") {
        std::cerr << "Check failed: arr1 name1" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(2)->getElement("name")->getValue() != "i3") {
        std::cerr << "Check failed: arr1 name2" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(3)->getValue() != "very different array items type") {
        std::cerr << "Check failed: arr1 name3" << std::endl;
        ret = -1;
    }

    pArr1->removeElement(1);

    if (pArr1->getLength() != 3) {
        std::cerr << "Check failed: arr1 len (2)" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(0)->getElement("name")->getValue() != "i1") {
        std::cerr << "Check failed: arr1 name0 (2)" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(1)->getElement("name")->getValue() != "i3") {
        std::cerr << "Check failed: arr1 name1 (2)" << std::endl;
        ret = -1;
    }

    if (pArr1->getElement(2)->getValue() != "very different array items type") {
        std::cerr << "Check failed: arr1 name2 (2)" << std::endl;
        ret = -1;
    }

    return ret;
}