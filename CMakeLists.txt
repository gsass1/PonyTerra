cmake_minimum_required(VERSION 2.6)
project(PonyTerra)


MACRO(ADD_PRECOMPILED_HEADER _targetName _input)
  GET_FILENAME_COMPONENT(_inputWe ${_input} NAME_WE)
  SET(pch_source ${_inputWe}.cpp)
  FOREACH(arg ${ARGN})
    IF(arg STREQUAL FORCEINCLUDE)
      SET(FORCEINCLUDE ON)
    ELSE(arg STREQUAL FORCEINCLUDE)
      SET(FORCEINCLUDE OFF)
    ENDIF(arg STREQUAL FORCEINCLUDE)
  ENDFOREACH(arg)
 
  IF(MSVC)
    GET_TARGET_PROPERTY(sources ${_targetName} SOURCES)
    SET(_sourceFound FALSE)
    FOREACH(_source ${sources})
      SET(PCH_COMPILE_FLAGS "")
      IF(_source MATCHES \\.\(cc|cxx|cpp\)$)
	GET_FILENAME_COMPONENT(_sourceWe ${_source} NAME_WE)
	IF(_sourceWe STREQUAL ${_inputWe})
	  SET(PCH_COMPILE_FLAGS "${PCH_COMPILE_FLAGS} /Yc${_input}")
	  SET(_sourceFound TRUE)
	ELSE(_sourceWe STREQUAL ${_inputWe})
	  SET(PCH_COMPILE_FLAGS "${PCH_COMPILE_FLAGS} /Yu${_input}")
	  IF(FORCEINCLUDE)
	    SET(PCH_COMPILE_FLAGS "${PCH_COMPILE_FLAGS} /FI${_input}")
	  ENDIF(FORCEINCLUDE)
	ENDIF(_sourceWe STREQUAL ${_inputWe})
	SET_SOURCE_FILES_PROPERTIES(${_source} PROPERTIES COMPILE_FLAGS "${PCH_COMPILE_FLAGS}")
      ENDIF(_source MATCHES \\.\(cc|cxx|cpp\)$)
    ENDFOREACH()
    IF(NOT _sourceFound)
      MESSAGE(FATAL_ERROR "A source file for ${_input} was not found. Required for MSVC builds.")
    ENDIF(NOT _sourceFound)
  ENDIF(MSVC)
 
  IF(CMAKE_COMPILER_IS_GNUCXX)
    GET_FILENAME_COMPONENT(_name ${_input} NAME)
    SET(_source "${CMAKE_CURRENT_SOURCE_DIR}/${_input}")
    SET(_outdir "${CMAKE_CURRENT_BINARY_DIR}/${_name}.gch")
    MAKE_DIRECTORY(${_outdir})
    SET(_output "${_outdir}/.c++")
    
    STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
    SET(_compiler_FLAGS ${${_flags_var_name}})
    
    GET_DIRECTORY_PROPERTY(_directory_flags INCLUDE_DIRECTORIES)
    FOREACH(item ${_directory_flags})
      LIST(APPEND _compiler_FLAGS "-I${item}")
    ENDFOREACH(item)
 
    GET_DIRECTORY_PROPERTY(_directory_flags DEFINITIONS)
    LIST(APPEND _compiler_FLAGS ${_directory_flags})
 
    SEPARATE_ARGUMENTS(_compiler_FLAGS)
    MESSAGE("${CMAKE_CXX_COMPILER} -DPCHCOMPILE ${_compiler_FLAGS} -x c++-header -o {_output} ${_source}")
    ADD_CUSTOM_COMMAND(
      OUTPUT ${_output}
      COMMAND ${CMAKE_CXX_COMPILER} ${_compiler_FLAGS} -x c++-header -o ${_output} ${_source}
      DEPENDS ${_source} )
    ADD_CUSTOM_TARGET(${_targetName}_gch DEPENDS ${_output})
    ADD_DEPENDENCIES(${_targetName} ${_targetName}_gch)
    SET_TARGET_PROPERTIES(${_targetName} PROPERTIES COMPILE_FLAGS "-include ${_name} -Winvalid-pch")
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDMACRO()



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
	src/Console.cpp
	src/Console.h
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
	src/GUI_IngameMenu.cpp
	src/GUI_IngameMenu.h
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
	src/Precompiled.h
	src/Precompiled.cpp
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

add_precompiled_header(Game Precompiled.h)

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
