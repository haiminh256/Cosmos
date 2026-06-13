#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <string>

#ifdef COSMOS_BUILD_DLL
    #define COSMOS_API __declspec(dllexport)
#else
    #define COSMOS_API __declspec(dllimport)
#endif