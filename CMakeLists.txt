project(GameProject)

add_executable(
    Game
    src/main.cpp
)

find_package(SFML 2 REQUIRED graphics)

include_directories(include ${SFML_INCLUDE_DIR})