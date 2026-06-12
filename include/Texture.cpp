#include <Engine/Texture.h>
#include <EngineEnv.h>

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
        Engine_Log("Texture::Load success: " + path, "INFO");
        return texture;
    }
    Engine_Log("Texture::Load failed: " + path + (std::string)SDL_GetError(), "ERROR");
    return texture;
}

SDL_Texture* Texture::Get() const
{
    return texture;
}