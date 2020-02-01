cmake_minimum_required(VERSION 3.5)
project(erat)

if(APPLE)
    set(CMAKE_CXX_COMPILER g++-7)
endif()

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

include_directories(src)

add_executable(erat
        main.cpp
        src/Shell.cpp
        src/Shell.hpp
        src/String.cpp
)
	
target_link_libraries(erat pthread)
