file(GLOB_RECURSE COSMOS_SOURCES
    "*.cpp"
)

add_library(Cosmos SHARED
    ${COSMOS_SOURCES}
)

target_compile_definitions(Cosmos PRIVATE
    COSMOS_BUILD_DLL
)

target_include_directories(Cosmos PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/vendors/SDL/include
    ${PROJECT_SOURCE_DIR}/vendors/SDL_image/include 
    ${PROJECT_SOURCE_DIR}/vendors/SDL_mixer/include
    ${PROJECT_SOURCE_DIR}/vendors/spdlog/include
)

target_link_libraries(Cosmos PUBLIC
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    spdlog::spdlog
)