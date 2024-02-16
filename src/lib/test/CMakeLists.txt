set(LIB_NAME ${LIB_NAME}Test)

# According to this guide https://google.github.io/googletest/quickstart-cmake.html

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${LIB_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/yaml_test.cpp
)

target_link_libraries(${LIB_NAME}
  PRIVATE
    wsjcpp::yamlcpp
    GTest::gtest_main
)
