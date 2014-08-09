cmake_minimum_required(VERSION 2.6)
project(PonyTerra)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(TinyXML REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/nsengine/include/NSEngine")
include_directories("${CMAKE_SOURCE_DIR}/nsengine/include/NSUtilLib")

if(WIN32)
include_directories(C:/Include)
endif()

if(WIN32)

add_definitions("-D_CRT_SECURE_NO_WARNINGS -DPONYTERRA_EXPORTS")

endif()

if(NOT WIN32)

add_definitions("-std=c++11 -fPIC -D_LINUX")

endif()

option(CI "CI" OFF)

set(PONYTERRA_MAJOR "0")
set(PONYTERRA_MINOR "0")
set(PONYTERRA_REV "0")

set(PONYTERRA_SOURCES
	src/Component_Animation.cpp
	src/Component_Animation.h
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
	src/NoiseGenerator.cpp
	src/NoiseGenerator.h
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

add_library(Game SHARED ${PONYTERRA_SOURCES})

set(LIBRARIES
	${TINYXML_LIBRARIES}
)

if(WIN32)

list(APPEND LIBRARIES "${CMAKE_SOURCE_DIR}/nsengine/lib/NSUtilLib.lib")

else()

list(APPEND LIBRARIES "${CMAKE_SOURCE_DIR}/nsengine/lib/libNSUtilLib.a")

endif()

target_link_libraries(Game ${LIBRARIES})

if(NOT WIN32)

set_target_properties(Game PROPERTIES PREFIX "")

endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/nsengine/bin/ DESTINATION .)
install(TARGETS Game DESTINATION .)

set(CPACK_PACKAGE_NAME "PonyTerraInstaller")
set(CPACK_PACKAGE_VENDOR "Gian Sass")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "PonyTerra")

if(${CI} STREQUAL "ON")

set(CPACK_PACKAGE_VERSION "${PONYTERRA_MAJOR}.${PONYTERRA_MINOR}.${PONYTERRA_REV}.${PONYTERRA_BUILD}")

else()

set(CPACK_PACKAGE_VERSION "${PONYTERRA_MAJOR}.${PONYTERRA_MINOR}.${PONYTERRA_REV}")

endif()

set(CPACK_PACKAGE_VERSION_MAJOR ${PONYTERRA_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PONYTERRA_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PONYTERRA_REV})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "PonyTerra")
set(CPACK_PACKAGE_FILE_NAME "PonyTerra-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}")

include(CPack)