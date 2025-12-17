# MIT License
#
# Copyright (c) 2019-2025 wsjcpp
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Official Source Code: https://github.com/wsjcpp/wsjcpp-yaml

cmake_minimum_required(VERSION 3.0)

project(wsjcpp-yaml)

# include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp-yaml_SOURCE_DIR})

# Sources

set (WSJCPP_LIBRARIES "")
set (WSJCPP_INCLUDE_DIRS "")
set (WSJCPP_SOURCES "")

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "src/wsjcpp_yaml.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_yaml.cpp")
list (APPEND WSJCPP_SOURCES "src/main.cpp")
list (APPEND WSJCPP_SOURCES "src/examples/example_iterate_array.cpp")
list (APPEND WSJCPP_SOURCES "src/examples/example_operators.cpp")

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable ("wsjcpp-yaml" ${WSJCPP_SOURCES})

if(WIN32)
    target_link_libraries("wsjcpp-yaml" ${WSJCPP_LIBRARIES} )
else()
    target_link_libraries("wsjcpp-yaml" -lpthread ${WSJCPP_LIBRARIES} )
endif()

install(
    TARGETS
        "wsjcpp-yaml"
    RUNTIME DESTINATION
        /usr/bin
)

# enable testing functionality
enable_testing()
add_subdirectory(src/tests)