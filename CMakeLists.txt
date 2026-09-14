cmake_minimum_required(VERSION 3.16)

project(BankSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB BANK_SYSTEM_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/大作业/*.cpp")
add_executable(BankSystem ${BANK_SYSTEM_SOURCES})
target_include_directories(BankSystem PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/大作业")

if(MSVC)
    target_compile_options(BankSystem PRIVATE /W3 /utf-8)
else()
    target_compile_options(BankSystem PRIVATE -Wall -Wextra -Wpedantic)
endif()
