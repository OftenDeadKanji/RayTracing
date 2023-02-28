cmake_minimum_required(VERSION 3.23)
project (RealTimeRayTracing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(RTRT "")
add_subdirectory("src")
add_subdirectory("dependencies/src/")

include_directories("dependencies/include/")

#target_precompile_headers(RTRT PRIVATE 
#	# C++ std
#	<cstdint>
#	<string>
#	<vector>
#	<memory>
#
#	# deps
#	"dependencies/include/Eigen/Dense"
#	"dependencies/include/glad/glad.h"
#	"dependencies/include/GLFW/glfw3.h"
#
#	# this project
#	"src/Math/mathUtils.hpp"
#	"src/Utils/nonCopyable.hpp"
#)

set(MSG_PREFIX "[RTRT] -- ")
set(LIB_DIR "dependencies/lib/")

if(MSVC)
	message("${MSG_PREFIX}MSVC compiler detected!")
	string(APPEND LIB_DIR "msvc/")
else()
	message(FATAL_ERROR "${MSG_PREFIX}Unknown compiler detected! - ${CMAKE_BUILD_TYPE}")
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	message("${MSG_PREFIX}Debug configuration detected!")
	string(APPEND LIB_DIR "Debug/")

	add_compile_definitions(_DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
	message("${MSG_PREFIX}Release configuration detected!")
	string(APPEND LIB_DIR "Release/")


	add_compile_definitions(_RELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES "Dist")
	message("${MSG_PREFIX}Distribution configuration detected!")
	string(APPEND LIB_DIR "Release/")

	add_compile_definitions(_DIST)
else()
	message(FATAL_ERROR "${MSG_PREFIX}Unknown configuration detected! - ${CMAKE_BUILD_TYPE}")
endif()

message("${MSG_PREFIX}Libraries will be search in \"${LIB_DIR}\" subdirectory")

find_library(LIB_OPENGL NAMES opengl32 REQUIRED)
find_library(LIB_GLFW NAMES glfw3 PATHS ${LIB_DIR} REQUIRED)

target_link_libraries(RTRT PRIVATE glad ${LIB_OPENGL} ${LIB_GLFW})