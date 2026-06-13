#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <EngineEnv.h>
#include <string>
namespace Cosmos {
    class COSMOS_API Texture {
    public:
        Texture();
        ~Texture();

        bool Load(SDL_Renderer* renderer,
                const std::string& path);

        SDL_Texture* Get() const;

    private:
        SDL_Texture* texture;
    };
}