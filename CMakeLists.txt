cmake_minimum_required(VERSION 3.1)

project(3bp)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# set this one somehwere
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
    ${GMOCK_ROOT}/include
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
)

add_executable(
    3bp
    src/main.cpp
    include/Game.h
    src/Game.cpp
)

add_executable(
    Test
    src/RunTests.cpp
)

target_link_libraries(3bp-lib sfml-graphics)
target_link_libraries(3bp sfml-graphics 3bp-lib)
target_link_libraries(Test sfml-graphics ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} 3bp-lib)