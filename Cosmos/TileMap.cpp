#include <Engine/TileMap.h>
#include <EngineEnv.h>

namespace Cosmos {
    TileMap::TileMap(int tileSize)
    {
        this->tileSize = tileSize;
        texture = nullptr;
    }

    void TileMap::Load(const std::vector<std::vector<int>>& mapData)
    {
        map = mapData;
    }

    void TileMap::SetTexture(Texture* tex)
    {
        texture = tex;
    }

    void TileMap::Render(SDL_Renderer* renderer)
    {

        if (!texture) return;

        SDL_FRect src;
        SDL_FRect dst;

        for (int y = 0; y < (int)map.size(); y++)
        {
            for (int x = 0; x < (int)map[y].size(); x++)
            {
                int tileType = map[y][x];


                if (tileType == 0) continue; 
                src.x = (float)((tileType - 1) * tileSize); 
                src.y = 0.0f;
                src.w = (float)tileSize;
                src.h = (float)tileSize;
                dst = {
                    x * (float)tileSize,
                    y * (float)tileSize,
                    (float)tileSize,
                    (float)tileSize
                };

                SDL_RenderTexture(renderer, texture->Get(), &src, &dst);
            }
        }
    }

    bool TileMap::IsSolid(int x, int y)
    {

        if (y < 0 || y >= (int)map.size()) return false;
        if (x < 0 || x >= (int)map[0].size()) return false;

        int tileType = map[y][x];

        if (tileType == 1 || tileType == 2)
        {
            return true;
        }


        return false;
    }
}