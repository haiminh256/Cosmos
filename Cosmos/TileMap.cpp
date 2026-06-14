#include <Engine/TileMap.h>
#include <EngineEnv.h>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

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

    bool TileMap::LoadFromCSV(const std::string& path)
    {
        std::ifstream in(path);
        if (!in.is_open()) return false;

        std::vector<std::vector<int>> newMap;
        std::string line;
        size_t maxWidth = 0;

        auto trim = [](std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
            s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
        };

        while (std::getline(in, line))
        {
            if (line.empty()) continue;
            std::vector<int> row;
            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ','))
            {
                trim(cell);
                if (cell.empty())
                {
                    row.push_back(0);
                    continue;
                }
                try {
                    int v = std::stoi(cell);
                    row.push_back(v);
                } catch (...) {
                    row.push_back(0);
                }
            }
            maxWidth = std::max(maxWidth, row.size());
            newMap.push_back(std::move(row));
        }

        if (newMap.empty()) return false;

        for (auto &r : newMap) if (r.size() < maxWidth) r.resize(maxWidth, 0);

        map = std::move(newMap);
        return true;
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