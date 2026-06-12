#include <Engine/Texture.h>
#include <Engine/Log.h>
#include <EngineEnv.h>


namespace Cosmos {
    Texture::Texture()
    {
        texture = nullptr;
    }

    Texture::~Texture()
    {
        if(texture)
        {
            SDL_DestroyTexture(texture);
        }
    }

    bool Texture::Load(SDL_Renderer* renderer,
                    const std::string& path)
    {
        texture = IMG_LoadTexture(renderer,
                                path.c_str());
        if(texture != nullptr){
            CORE_INFO("Texture::Load success: " + path);
            return texture;
        }
        CORE_ERROR("Texture::Load failed: " + path + (std::string)SDL_GetError());
        return texture;
    }

    SDL_Texture* Texture::Get() const
    {
        return texture;
    }
}