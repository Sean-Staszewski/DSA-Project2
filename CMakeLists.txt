cmake_minimum_required(VERSION 3.28)
project(DSAProject2)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0  # Use the latest stable version
)
FetchContent_MakeAvailable(Catch2)

add_executable(DSAProject2 main.cpp
        AdjacencyList.h
        AdjacencyList.cpp
)

add_executable(tests test.cpp
        AdjacencyList.h
        AdjacencyList.cpp)

target_link_libraries(DSAProject2 PRIVATE Catch2::Catch2)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
