cmake_minimum_required(VERSION 3.14)

project(MidTermPrac)

include(FetchContent)

FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.0.0"
)

FetchContent_MakeAvailable(GSL)

add_executable(MidTermPrac main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


target_link_libraries(MidTermPrac PRIVATE GSL)