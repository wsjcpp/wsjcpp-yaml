set(LIB_NAME yamlcpp)

add_library(${LIB_NAME} STATIC)
add_library(wsjcpp::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories(${LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_sources(${LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/wsjcpp/yaml/yaml.h
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/yaml.cpp
)