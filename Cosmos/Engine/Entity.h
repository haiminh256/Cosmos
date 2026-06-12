#pragma once

#include <EngineEnv.h>
#include <Engine/Texture.h>
#include <Engine/TileMap.h>

namespace Cosmos {
    class Entity {
    public:
        virtual ~Entity() = default;

        void SetTexture(Texture* tex);

        virtual void Update(float dt) = 0;
        virtual void Render(SDL_Renderer* renderer);
        void CheckMapCollisionX(TileMap& tileMap);
        void CheckMapCollisionY(TileMap& tileMap);

    protected:
        SDL_FRect rect;
        Texture* texture;
        float velocityX;
        float velocityY;
        bool isGrounded;
    };
}