cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(rapidJSONExample rapidJSONExample.cpp)
add_executable(supersearch main.cpp AvlPair.cpp Parser.cpp ParsedQuery.cpp ParsedDoc.cpp UserInterface.cpp IndexHandler.cpp)
# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)

include(CTest)

# add_executable(tests_avltree AvlTreeTests.cpp AvlPair.cpp)
#add_test(NAME TestAVL COMMAND tests_avltree)

add_executable(fullAVLTest fullAVLTest.cpp AvlPair.cpp)
add_test(NAME testAVL COMMAND fullAVLTest)
