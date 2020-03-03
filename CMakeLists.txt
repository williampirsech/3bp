add_executable(
    Game
    src/main.cpp
)

find_package(SFML 2 REQUIRED audio graphics window system network)

include_directories(include ${SFML_INCLUDE_DIR})