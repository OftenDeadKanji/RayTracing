cmake_minimum_required(VERSION 3.23)
project (RealTimeRayTracing)

add_executable(RTRT "")
add_subdirectory("src")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories("dependencies/include/")

set(MSG_PREFIX "[RTRT] -- ")

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	message("${MSG_PREFIX}Debug configuration detected!")

	add_compile_definitions(_DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
	message("${MSG_PREFIX}Release configuration detected!")

	add_compile_definitions(_RELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES "Dist")
	message("${MSG_PREFIX}Distribution configuration detected!")

	add_compile_definitions(_DIST)
else()
	message(FATAL_ERROR "${MSG_PREFIX}Unknown configuration detected! - ${CMAKE_BUILD_TYPE}")
endif()
