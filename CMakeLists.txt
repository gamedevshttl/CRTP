#cmake -B build -S .
cmake_minimum_required(VERSION 3.10)

project(CRTP)

set(SOURCE_CODE 
		src/main.cpp
		src/ClassicPolymorphism.h
		src/CRTP.h
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
	set(CMAKE_CXX_STANDARD 17)
endif()

add_executable(CRTP ${SOURCE_CODE})
