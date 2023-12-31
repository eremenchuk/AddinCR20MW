cmake_minimum_required(VERSION 3.10)
project(CR20MW)
set(TARGET CR20MW)

set(CXX_STANDARD 17)

add_library(${TARGET} SHARED
	src/AddInNative.cpp
	src/AddInNative.def
	src/AddInNative.h
	src/AddInNative.rc
	src/CR20MW.cpp
	src/CR20MW.h
	src/Reader.cpp
	src/Reader.h)

target_compile_definitions(${TARGET} PRIVATE UNICODE _UNICODE)
target_include_directories(${TARGET} PRIVATE include)
target_link_libraries(${TARGET}
	C:/MifareReaderLib/reader.lib)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH})
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})

if(UNIX)
	if(APPLE)
		set(MySuffix1 "Mac")
	else(APPLE)
		set(MySuffix1 "Lin")
	endif(APPLE)

	if(TARGET_PLATFORM_32)
		set(MySuffix2 "32")
	else()
		set(MySuffix2 "64")
	endif()
else(UNIX)
	if(NOT MSVC)
		message(FATAL_ERROR "Must be compiled with MSVC on Windows")
	endif(NOT MSVC)

	set(MyPrefix "lib")
	set(MySuffix1 "Win")
endif(UNIX)

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME ${PROJECT_NAME}${MySuffix2}
	POSITION_INDEPENDENT_CODE ON
	CXX_STANDARD_REQUIRED ON
	CXX_STANDARD 17
)

if(UNIX)
	if(TARGET_PLATFORM_32)
		set(CMAKE_C_FLAGS "-m32 ${CMAKE_C_FLAGS}")
		set(CMAKE_CXX_FLAGS "-m32 ${CMAKE_CXX_FLAGS}")
	else(TARGET_PLATFORM_32)
		set(CMAKE_C_FLAGS "-m64 ${CMAKE_C_FLAGS}")
		set(CMAKE_CXX_FLAGS "-m64 ${CMAKE_CXX_FLAGS}")
	endif()

	target_link_libraries(${PROJECT_NAME} -static-libstdc++)
else(UNIX)
	add_definitions(/MT)
	set(CMAKE_SUPPRESS_REGENERATION 1)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
	target_compile_definitions(${TARGET} PRIVATE _WINDOWS
		_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
	target_compile_options(${TARGET} PRIVATE /utf-8)
endif(UNIX)
