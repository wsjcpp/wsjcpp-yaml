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

file(GLOB ALL_TESTS
     "test_*.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY tests)

list (APPEND TEST_YAML_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../wsjcpp_yaml.cpp")

foreach(_TEST ${ALL_TESTS})
    get_filename_component(TESTNAME ${_TEST} NAME_WE)
    add_executable(${TESTNAME}
        ${_TEST}
        ${TEST_YAML_SOURCES}
    )
    target_link_libraries(${TESTNAME} -lpthread ${WSJCPP_LIBRARIES})

    add_test(
      NAME ${TESTNAME}
      COMMAND $<TARGET_FILE:${TESTNAME}>
    )
    message(${CMAKE_CURRENT_BINARY_DIR}/tests)
    set_target_properties (${TESTNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY tests)
endforeach()
