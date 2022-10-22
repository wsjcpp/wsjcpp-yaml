# wsjcpp-yaml

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp-yaml.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp-yaml) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-yaml.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-yaml) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-yaml.svg)](https://github.com/wsjcpp/wsjcpp-yaml) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-yaml.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-yaml/network/members) [![Total alerts](https://img.shields.io/lgtm/alerts/g/wsjcpp/wsjcpp-yaml.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-yaml/alerts/) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wsjcpp/wsjcpp-yaml.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-yaml/context:cpp)

C++ YAML parser/reader and writer of *.yaml/*.yml files with keeping user formatting 

## Integrate to your c++ project

include files:

- src/wsjcpp_yaml.cpp
- src/wsjcpp_yaml.h

or just

```
$ wsjcpp install https://github.com/wsjcpp/wsjcpp-yaml:master
```

## Example usage:

In you main file configure logger:

```cpp

#include <string.h>
#include <iostream>
#include "wsjcpp_yaml.h"

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";

    // now you can use WsjcppYaml
    WsjcppYaml yaml;
    std::string sYaml =
        "# yaml content\n"
        "yaml1: nice format\n"
        "some-map: value1\n"
        "some-map2: value2\n"
        "some-array:\n"
        "  - test1 \n"
        "  - test2 \n"
        "some-am: # array + map element \n"
        "  - p1: v1 \n"
        "    p2: v2 \n"
        "  - p1: v3 \n"
        "    p2: v4 \n"
        "param2: 111\n";
    std::string sError;
    if (!yaml.loadFromString("my-local.yaml", sYaml, sError)) {
        yaml.throw_err(TAG, sError);
        return -1;
    }

    std::cout << "yaml is " << yaml["yaml1"].valStr() << std::endl;
    std::cout << "some-map is " << yaml["some-map"].valStr() << std::endl;
    std::cout << "some-map2 is " << yaml["some-map2"].valStr() << std::endl;
    std::cout << "some-array has " << std::to_string(yaml["some-array"].valStr()) << std::endl;
    std::cout << "some-array element 0 is " << yaml["some-array"][0].valStr() << std::endl;
    std::cout << "some-array element 1 is " << yaml["some-array"][1].valStr() << std::endl;
    std::cout << "some-am has " << std::to_string(yaml["some-am"].size()) << std::endl;
    std::cout << "some-am is array: " << (yaml["some-am"].isArray() ? "yes" : "no") << std::endl;
    std::cout << "some-am has comment " << yaml["some-am"].comment() << std::endl;
    std::cout << "some-am element 0 : p1 is  " << yaml["some-am"][0]["p1"].valStr() << std::endl;
    std::cout << "some-am element 0 : p2 is  " << yaml["some-am"][0]["p2"].valStr() << std::endl;
    std::cout << "some-am element 1 : p1 is  " << yaml["some-am"][1]["p1"].valStr() << std::endl;
    std::cout << "some-am element 1 : p2 is  " << yaml["some-am"][1]["p2"].valStr() << std::endl;

    return 0;
}

```

## a little doc:

### class methods (WsjcppYaml)

**`WsjcppYaml()`**

Just a constructor

**`void clear();`**

Clear all nodes

**`void setLogger(IWsjcppYamlLog *pLog);`**

If you wanna use custom logger

```cpp
class MyLogger : public IWsjcppYamlLog {
    public:
        // IWsjcppYamlLog
        virtual void err(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [error] : " << sMessage << std::endl;
        };
        virtual void throw_err(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [critical_error] : " << sMessage << std::endl;
            throw std::runtime_error(TAG + " [critical_error] : " + sMessage);
        };
        virtual void warn(const std::string &TAG, const std::string &sMessage) override {
            std::cerr << TAG << " [warn] : " << sMessage << std::endl;
        };
        virtual void info(const std::string &TAG, const std::string &sMessage) override {
            std::cout << TAG << " [info] : " << sMessage << std::endl;
        };
};

MyLogger *pLogger = new MyLogger();
WsjcppYaml yaml;
yaml.setLogger(pLogger);
```

**`bool loadFromFile(const std::string &sFileName, std::string &sError);`**

load yaml from file

Will retrun:
- `true` - success 
- `false` - failed (information about error will be in sError)

**`bool saveToFile(const std::string &sFileName, std::string &sError);`**

save yaml to file

Will retrun:
- `true` - success 
- `false` - failed (information about error will be in sError)

**`bool loadFromString(const std::string &sBufferName, const std::string &sBuffer, std::string &sError);`**

load yaml from string

**`bool saveToString(std::string &sBuffer, std::string &sError);`**

save yaml to string

sBuffer - here will be result.

Will retrun:
- `true` - success 
- `false` - failed (information about error will be in sError)

**`WsjcppYamlNode *getRoot();`**

return root node

**`WsjcppYamlCursor getCursor() const;`**

return cursor (for walk by yaml tree)

**`WsjcppYamlCursor operator[](int idx) const;`**

return cursor if current element is array else will be error

**`WsjcppYamlCursor operator[](const std::string &sName) const;`**

return cursor if current element is map else will be error

#### Static methods (WsjcppYaml)

**`bool readTextFile(const std::string &sFilename, std::string &sOutputContent, std::string &sError);`**

static method. Just read text file

Will retrun:
- `true` - success 
- `false` - failed (information about error will be in sError)

**`bool writeFile(const std::string &sFilename, const std::string &sContent);`**

static method. Just write text to file

Will retrun:
- `true` - success 
- `false` - failed 

**`static std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");`**

static method. left trim

**`static std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");`**

static method. right trim

**`static std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");`**

static method. left and right trim

**`static std::string toLower(const std::string &str);`**

static method. to lower characters (will be work only for latin coding)

#### methods for logging (WsjcppYaml)

**`void err(const std::string &TAG, const std::string &sMessage);`**

default: print to std::cerr

But you can override by `setLogger`

**`void throw_err(const std::string &TAG, const std::string &sMessage);`**

default: print to std::cerr and throw std::exception

But you can override by `setLogger`

**`void warn(const std::string &TAG, const std::string &sMessage);`**

default: print to std::cerr

But you can override by `setLogger`

**`void info(const std::string &TAG, const std::string &sMessage);`**

default: print to std::cout

But you can override by `setLogger`


### class method (WsjcppYamlCursor)

WsjcppYamlCursor - keep a pointer to node ()


**`bool isNull() const;`**

return `true` if node is null or undefined


**`bool isUndefined() const;`**

return `true` if node is undefined.
It's possible if definintion in yaml without value like a `some: ` - undefined node

**`bool isValue() const;`**

return `true` if node is a simple type with a value

**`bool isArray() const;`**

return `true` if node is a array

**`size_t size() const;`**

return size of array if node is a array

**`bool isMap() const;`**

return `true` if node is map

**`std::vector<std::string> keys() const;`**

return list of keys if node is map

**`bool hasKey(const std::string &sKey) const;`**

return true if node is map and key exists

**`std::string comment();`**

return user comment or empty for node

**`WsjcppYamlCursor &comment(const std::string& sComment);`**

set new comment

**`std::string valStr();`**

return value as string

example: `yaml["some"].valStr()`

**`WsjcppYamlCursor &val(const std::string &sValue);`**

set new string value

**`WsjcppYamlCursor &val(const char *sValue);`**

set new string value

**`int valInt();`**

return value as integer

**`WsjcppYamlCursor &val(int nValue);`**

set new integer value

**`bool valBool();`**

return value as integer

**`WsjcppYamlCursor &val(bool bValue);`**

set new boolean value

**`WsjcppYamlNode *node();`**

return pointer to node

**`WsjcppYamlCursor operator[](int idx) const;`**

return node by index if current node is array

example: `yaml["somearr"][0]`

**`WsjcppYamlCursor operator[](const std::string &sName) const;`**

return node by index if current node is map

example: `yaml["some_map"]["el1"]`

