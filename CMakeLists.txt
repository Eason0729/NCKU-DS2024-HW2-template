cmake_minimum_required(VERSION 3.30)
project(HW2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

find_package(ut REQUIRED)

add_executable(HW2 fheap.c main.c)

target_include_directories(HW2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

foreach (TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME}_test ${TEST_SOURCE})
    target_sources(${TEST_NAME}_test PRIVATE fheap.c)
    target_link_libraries(${TEST_NAME}_test Boost::ut)
endforeach ()

add_custom_target(package COMMAND $ENV{HOME}/.cargo/bin/nedry --input=../main.c bundle)