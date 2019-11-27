cmake_minimum_required(VERSION 3.0)

project(unit-tests)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${unit-tests_SOURCE_DIR})

set (WSJCPP_LIBRARIES "")
set (WSJCPP_INCLUDE_DIRS "")
set (WSJCPP_SOURCES "")

# Sources

# wsjcpp-core
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp-core/wsjcpp_core.cpp")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp-core/wsjcpp_core.h")
list (APPEND WSJCPP_INCLUDE_DIRS "../src.wsjcpp/wsjcpp-core/")

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
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_hierarchical_map.h")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_hierarchical_map.cpp")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_array_included_map.h")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_array_included_map.cpp")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_comments.h")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_comments.cpp")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_quotes.h")
list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_quotes.cpp")

# list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_all.h")
# list (APPEND WSJCPP_SOURCES "./src/unit_test_yaml_parser_all.cpp")

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
