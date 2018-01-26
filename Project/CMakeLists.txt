set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SteeringsFest/cmake_modules" ${CMAKE_MODULE_PATH})
FIND_PACKAGE(SFML 2 REQUIRED graphics window system)

SET(SOURCES src/main.cpp src/Grid.cpp src/Grid.h src/Tile.cpp src/Tile.h src/GameObject.cpp src/GameObject.h src/Game.cpp src/Game.h)
SET(EXECUTABLE_NAME Project)
add_executable(${EXECUTABLE_NAME} ${SOURCES})

IF(SFML_FOUND)
    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()