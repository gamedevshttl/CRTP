cmake_minimum_required(VERSION 2.8)

project(CRTP)

set(SOURCE_CODE 
		src/main.cpp
		src/ClassicPolymorphism.h
		src/CRTP.h
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

add_executable(CRTP ${SOURCE_CODE})

#target_link_libraries(CRTP)

