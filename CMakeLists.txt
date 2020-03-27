cmake_minimum_required(VERSION 3.1)

project(3bp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# set this one somehwere
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

find_package(RapidXML)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
    ${GMOCK_ROOT}/include
    ${RAPIDXML_INCLUDE_DIR}
)

add_library(
    3bp-lib
    include/Util.h
    include/Movable.h
    src/Movable.cpp
    include/Dynamics.h
    src/Dynamics.cpp
    include/HUDItem.h
    include/FuelMeter.h
    src/FuelMeter.cpp
    include/Minimap.h
    src/Minimap.cpp
    include/Collision.h
    src/Collision.cpp
    include/MovableCreator.h
    src/MovableCreator.cpp
)

add_executable(
    3bp
    src/main.cpp
    include/Game.h
    src/Game.cpp
    ${RAPIDXML_INCLUDE_DIR}/rapidxml.hpp
    ${RAPIDXML_INCLUDE_DIR}/rapidxml_print.hpp
)

add_executable(
    Test
    src/Test/DynamicsTest.cpp
    src/Test/CollisionTest.cpp
)

target_link_libraries(3bp-lib sfml-graphics)
target_link_libraries(3bp sfml-graphics 3bp-lib)
target_link_libraries(Test sfml-graphics ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} 3bp-lib)