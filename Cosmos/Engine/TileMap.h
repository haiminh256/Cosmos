#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <Engine/Texture.h>

namespace Cosmos {
    class COSMOS_API TileMap {
    public:
        TileMap(int tileSize);

        void Load(const std::vector<std::vector<int>>& map);
        void SetTexture(Texture* tex);

        void Render(SDL_Renderer* renderer);

        bool IsSolid(int x, int y);

        int GetTileSize() const { return tileSize; }

    private:
        std::vector<std::vector<int>> map;
        Texture* texture;

        int tileSize;
    };
}