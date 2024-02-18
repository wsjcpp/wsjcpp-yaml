set(LIB_NAME yamlcpp)

option(WSJCPP_${LIB_NAME}_BUILD_TEST "Enable build and run unit test" ON)

add_library(${LIB_NAME} STATIC)
add_library(wsjcpp::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories(${LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_sources(${LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/wsjcpp/wsjcpp_yaml.h
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/wsjcpp_yaml.cpp
)

if(WSJCPP_${LIB_NAME}_BUILD_TEST)
  add_subdirectory(test)
endif()