cmake_minimum_required(VERSION 2.6)
project(PonyTerra)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories("${CMAKE_SOURCE_DIR}/nsengine/include/NSEngine")
include_directories("${CMAKE_SOURCE_DIR}/nsengine/include/NSUtilLib")

if(WIN32)

add_definitions("-D_CRT_SECURE_NO_WARNINGS -DPONYTERRA_EXPORTS")

endif()

if(NOT WIN32)

add_definitions("-std=c++11")

endif()

set(PONYTERRA_SOURCES
	src/Component_Physical.cpp
	src/Component_Physical.h
	src/Component_PlayerInput.cpp
	src/Component_PlayerInput.h
	src/DrawQuery.cpp
	src/DrawQuery.h
	src/Entity.h
	src/Entity.cpp
	src/EntityManager.h
	src/EntityManager.cpp
	src/EntityFactory.h
	src/EntityFactory.cpp
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

target_link_libraries(PonyTerra "${CMAKE_SOURCE_DIR}/nsengine/lib/NSUtilLib.lib")