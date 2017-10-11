set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
FIND_PACKAGE(SFML 2 REQUIRED graphics window system)

SET(SOURCES src/Vehicle.cpp src/Vehicle.hpp src/utils.hpp src/main.cpp src/Scene.cpp src/Scene.hpp src/Track.cpp src/Track.hpp src/utils.cpp src/elements/AbstractElement.cpp src/elements/AbstractElement.hpp src/elements/StaticElement.cpp src/elements/StaticElement.hpp)
SET(EXECUTABLE_NAME Steerings)
add_executable(${EXECUTABLE_NAME} ${SOURCES})

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} m)


IF(SFML_FOUND)
    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()