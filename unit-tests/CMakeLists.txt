cmake_minimum_required(VERSION 3.0)

project(unit-tests)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${unit-tests_SOURCE_DIR})

set (WSJCPP_LIBRARIES "")
set (WSJCPP_INCLUDE_DIRS "")
set (WSJCPP_SOURCES "")

# Sources

# wsjcpp-logger
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp-logger/fallen.cpp")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp-logger/fallen.h")
list (APPEND WSJCPP_INCLUDE_DIRS "../src.wsjcpp/wsjcpp-logger/")

# wsjcpp-yaml
list (APPEND WSJCPP_SOURCES "../src/wsjcpp_yaml.h")
list (APPEND WSJCPP_SOURCES "../src/wsjcpp_yaml.cpp")

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "../src")
list (APPEND WSJCPP_INCLUDE_DIRS "src")


list (APPEND WSJCPP_SOURCES "./src/unit_tests.h")
list (APPEND WSJCPP_SOURCES "./src/unit_tests.cpp")
list (APPEND WSJCPP_SOURCES "./src/unit_test_line_parser.h")
list (APPEND WSJCPP_SOURCES "./src/unit_test_line_parser.cpp")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_simple_array.h")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_simple_array.cpp")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_simple_map.h")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_simple_map.cpp")
# list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser.h")
# list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser.cpp")

list (APPEND WSJCPP_SOURCES "./src/main.cpp")

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable ("unit-tests" ${WSJCPP_SOURCES})

target_link_libraries("unit-tests" -lpthread ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        "unit-tests"
    RUNTIME DESTINATION
        /usr/bin
)