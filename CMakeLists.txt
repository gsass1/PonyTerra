cmake_minimum_required(VERSION 2.6)
project(PonyTerra)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

find_package(NSEngine REQUIRED)

include_directories(${NSENGINE_INCLUDE_DIR}/NSEngine/include)
include_directories(${NSENGINE_INCLUDE_DIR}/NSUtilLib/include)

if(WIN32)

add_definitions("-D_CRT_SECURE_NO_WARNINGS -DPONYTERRA_EXPORTS")

endif()

set(PONYTERRA_SOURCES
	src/Game.cpp
	src/Game.h
	src/GUI.h
	src/GUI_Loading.cpp
	src/GUI_Loading.h
	src/GUI_MenuFront.cpp
	src/GUI_MenuFront.h
	src/GUI_NewWorld.cpp
	src/GUI_NewWorld.h
	src/GUIManager.cpp
	src/GUIManager.h
	src/Level.cpp
	src/Level.h
	src/main.cpp
	src/Entity.h
	src/Entity.cpp
	src/Player.h
	src/Player.cpp
	src/Version.h
	src/VersionNumber.h
	src/Widget.cpp
	src/Widget.h
	src/Widget_Button.cpp
	src/Widget_Button.h
)

if(WIN32)

list(APPEND PONYTERRA_SOURCES src/version.rc)

endif()

add_library(PonyTerra SHARED ${PONYTERRA_SOURCES})
