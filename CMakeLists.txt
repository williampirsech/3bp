cmake_minimum_required(VERSION 3.1)

project(Game)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# set this one somehwere
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})

add_executable(Game src/main.cpp)
add_executable(RunTests src/first_tests.cpp)

target_link_libraries(Game sfml-graphics sfml-audio)
target_link_libraries(RunTests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})