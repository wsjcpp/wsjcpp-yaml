cmake_minimum_required(VERSION 3.0)

project(wsjcpp-yaml)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "../src")
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "../src/wsjcpp_yaml.h")
list (APPEND WSJCPP_SOURCES "../src/wsjcpp_yaml.cpp")
list (APPEND WSJCPP_SOURCES "./src/unit_tests.h")
list (APPEND WSJCPP_SOURCES "./src/unit_tests.cpp")
list (APPEND WSJCPP_SOURCES "./src/main.cpp")

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable ("wsjcpp-yaml-tests" ${WSJCPP_SOURCES})

target_link_libraries("wsjcpp-yaml-tests" -lpthread ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        "wsjcpp-yaml-tests"
    RUNTIME DESTINATION
        /usr/bin
)
