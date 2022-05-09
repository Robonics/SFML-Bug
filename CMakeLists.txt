cmake_minimum_required(VERSION 3.16)
project(testProgram CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)
    add_compile_options("$<$<CONFIG:DEBUG>:-fsanitize=address,undefined>")
	add_compile_options(-o ../bin/testProgram.exe)
    add_link_options("$<$<CONFIG:DEBUG>:-fsanitize=address,undefined>")
endif()

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(testProgram src/main.cpp)
target_link_libraries(testProgram PRIVATE sfml-graphics)
target_compile_definitions(testProgram PRIVATE FONT_PATH="${CMAKE_SOURCE_DIR}/data")

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.cpp *.h`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} `git ls-files *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(run COMMAND testProgram)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")