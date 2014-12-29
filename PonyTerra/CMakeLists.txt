set(PONYTERRA_SOURCES
	src/Component_Animation.cpp
	src/Component_Animation.h
	src/Component_Attributes.cpp
	src/Component_Attributes.h
	src/Component_Inventory.cpp
	src/Component_Inventory.h
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
	src/Inventory.cpp
	src/Inventory.h
	src/Item.cpp
	src/Item.h
	src/Item_HealthPotion.cpp
	src/Item_HealthPotion.h
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

include_directories(${PROJECT_SOURCE_DIR}/CRTDebug)
include_directories(${PROJECT_SOURCE_DIR}/NSEngine/include)
include_directories(${PROJECT_SOURCE_DIR}/NSUtilLib/include)

if(WIN32 AND NOT STANDALONE)

list(APPEND PONYTERRA_SOURCES src/version.rc)

endif()

if(STANDALONE)

add_library(Game ${PONYTERRA_SOURCES})

else()

add_library(Game SHARED ${PONYTERRA_SOURCES})

endif()

set(LIBRARIES
	${TINYXML_LIBRARIES}
)

if(NOT STANDALONE)

if(WIN32)

list(APPEND LIBRARIES "${CMAKE_SOURCE_DIR}/nsengine/lib/NSUtilLib.lib")

else()

list(APPEND LIBRARIES "${CMAKE_SOURCE_DIR}/nsengine/lib/libNSUtilLib.a")

endif()

endif()

if(STANDALONE)

target_link_libraries(Game NSUtilLib CRT)

else()

target_link_libraries(Game ${LIBRARIES})

endif()

if(NOT WIN32)

set_target_properties(Game PROPERTIES PREFIX "")

endif()

if(NOT STANDALONE)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/nsengine/bin/ DESTINATION .)
install(TARGETS Game DESTINATION .)

endif()