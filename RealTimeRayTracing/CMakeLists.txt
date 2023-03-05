cmake_minimum_required(VERSION 3.20)
project (RealTimeRayTracing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(RTRT "")
add_subdirectory("src")
add_subdirectory("dependencies/src/")

include_directories("dependencies/include/")

set(MSG_PREFIX "[RTRT] -- ")
set(LIB_DIR "dependencies/lib/")
set(LIBS "")

#
# Configuration detection
#

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	message("${MSG_PREFIX}Debug configuration detected!")
	string(APPEND LIB_DIR "debug/")

	add_compile_definitions(_DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
	message("${MSG_PREFIX}Release configuration detected!")
	string(APPEND LIB_DIR "release/")


	add_compile_definitions(_RELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES "Dist")
	message("${MSG_PREFIX}Distribution configuration detected!")
	string(APPEND LIB_DIR "release/")

	add_compile_definitions(_DIST)
else()
	message(FATAL_ERROR "${MSG_PREFIX}Unknown configuration detected! - ${CMAKE_BUILD_TYPE}")
endif()

#
# Compiler detection
#

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	message("${MSG_PREFIX}MSVC compiler detected!")
	string(APPEND LIB_DIR "msvc/")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	message("${MSG_PREFIX}GCC/G++ compiler detected!")
	string(APPEND LIB_DIR "gnu/")
else()
	message(FATAL_ERROR "${MSG_PREFIX}Unknown compiler detected! - ${CMAKE_CXX_COMPILER_ID}")
endif()


#
# Libraries files
#

message("${MSG_PREFIX}Libraries will be search in \"${LIB_DIR}\" subdirectory")

find_library(LIB_OPENGL NAMES opengl32 GL REQUIRED)
message("${MSG_PREFIX}OpenGL found - \"${LIB_OPENGL}\"")

find_library(LIB_GLFW NAMES glfw3 PATHS ${LIB_DIR} REQUIRED)
message("${MSG_PREFIX}GLFW found - \"${LIB_GLFW}\"")

target_link_libraries(RTRT PRIVATE glad ${LIB_OPENGL} ${LIB_GLFW})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_link_libraries(RTRT PRIVATE X11)
endif()