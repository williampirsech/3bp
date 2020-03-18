cmake_minimum_required(VERSION 3.1)

project(Game)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# set this one somehwere
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
)

add_executable(
    Game
    src/main.cpp
    include/Game.h
    src/Game.cpp
    include/Util.h
    include/Movable.h
    src/Movable.cpp
    include/MassiveMovable.h
    src/MassiveMovable.cpp
    include/ScreenMovement.h
    src/screenMovement.cpp
    include/Dynamics.h
    src/Dynamics.cpp
    include/HUDItem.h
    include/FuelMeter.h
    src/FuelMeter.cpp
    include/DirectionMeter.h
    src/DirectionMeter.cpp
)

target_link_libraries(Game sfml-graphics sfml-audio)