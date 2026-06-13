cmake_minimum_required(VERSION 3.20)

project(CosmosEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendors/SDL)
add_subdirectory(vendors/SDL_image)
add_subdirectory(vendors/SDL_mixer)
add_subdirectory(vendors/spdlog)

add_subdirectory(Cosmos)

add_executable(Game
    src/main.cpp
    src/Player.cpp
    src/Player.h
)

target_link_libraries(Game PRIVATE Cosmos)