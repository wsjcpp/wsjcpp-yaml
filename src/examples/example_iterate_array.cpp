#include <wsjcpp/yaml/yaml.h>

#include "examples.h"

void example_iterate_array() {

  std::string sTest =
      R"('2021-10-08':
          - code: '300209'
            focusstr: ''
          - code: '300047'
            focusstr: ''
          - code: '300970'
            focusstr: ''
          - code: '300288'
            focusstr: ''
        '2021-10-11':
          - code: '300162'
            focusstr: ''
          - code: '300209'
            focusstr: ''
          - code: '300972'
            focusstr: ''
          - code: '300159'
            focusstr: '')";

  WsjcppYaml yaml2;
  std::string sError;
  if (!yaml2.loadFromString("test", sTest, sError)) {
    std::cerr << sError << std::endl;
    return;
  }
  WsjcppYamlCursor cur = yaml2.getCursor();
  std::vector<std::string> vKeys = cur.keys();
  for (int i = 0; i < vKeys.size(); i++) {
    std::string sKey = vKeys[i];
    int nCount = cur[sKey].size(); // musts array
    for (int n = 0; n < nCount; n++) {
      WsjcppYamlCursor el = cur[sKey][n];
      std::cout << "code = " << el["code"].valInt() << "; focusstr = " << el["focusstr"].valStr() << ";" << std::endl;
    }
  }
}