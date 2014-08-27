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

add_subdirectory(PonyTerra)

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
