project(${CMAKE_PROJECT_NAME}_app)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true
        "*.h"
        "*.hpp"
        "*.hxx"
        "*.cpp"
        )

IF (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static -lstdc++ -lpthread")
ENDIF ()

add_executable(${CMAKE_PROJECT_NAME}_app ${SOURCES} Trie.hxx Node.hxx MainWindow.hxx)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core)