#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <string>

namespace Cosmos {
    inline void Engine_Log(std::string content, std::string logLevel){
        std::cout << "[" << logLevel << "]" << ":" << " " << content << std::endl;
    }
}