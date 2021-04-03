project(${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false
        "*.h"
        "*.hpp"
        "*.hxx"
        "*.cpp"
        )

set(SOURCES ${TEST_SOURCES} main.cpp checkTrie.cpp)

add_executable(${CMAKE_PROJECT_NAME}_tests ${SOURCES})
add_test(NAME ${CMAKE_PROJECT_NAME}_tests COMMAND ${SOURCES})