project(${CMAKE_PROJECT_NAME}_app)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true
        "*.h"
        "*.hpp"
        "*.hxx"
        "*.cpp"
        )

IF (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static -lstdc++ -lpthread")
ENDIF ()

add_executable(${CMAKE_PROJECT_NAME}_app ${SOURCES} Trie.hxx Node.hxx)

