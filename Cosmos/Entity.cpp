#include <Engine/Entity.h>
#include <EngineEnv.h>


namespace Cosmos {
    void Entity::SetTexture(Texture* tex)
    {
        texture = tex;
    }

    void Entity::Render(SDL_Renderer* renderer)
    {
        if(texture != nullptr)
        {
            SDL_RenderTexture(
                renderer,
                texture->Get(),
                nullptr,
                &rect
            );
        }
    }
    void Entity::CheckMapCollisionX(TileMap& tileMap)
    {
        int ts = tileMap.GetTileSize();
        if (ts <= 0) return;


        int px = (rect.x < 0) ? 0 : (int)rect.x;
        int py = (rect.y < 0) ? 0 : (int)rect.y;

        int startY = py / ts;
        int endY = (int)(rect.y + rect.h - 0.1f) / ts;

        if (velocityX > 0) {
            int colRight = (int)(rect.x + rect.w) / ts;
            for (int y = startY; y <= endY; y++) {
                if (tileMap.IsSolid(colRight, y)) {
                    rect.x = colRight * ts - rect.w;
                    velocityX = 0;
                    break;
                }
            }
        }
        else if (velocityX < 0) {
            int colLeft = px / ts;
            for (int y = startY; y <= endY; y++) {
                if (tileMap.IsSolid(colLeft, y)) {
                    rect.x = (colLeft + 1) * ts;
                    velocityX = 0;
                    break;
                }
            }
        }
    }

    void Entity::CheckMapCollisionY(TileMap& tileMap)
    {
        int ts = tileMap.GetTileSize();
        if (ts <= 0) return;

        int px = (rect.x < 0) ? 0 : (int)rect.x;
        int py = (rect.y < 0) ? 0 : (int)rect.y;

        int startX = px / ts;
        int endX = (int)(rect.x + rect.w - 0.1f) / ts;

        if (velocityY > 0) {
            int rowBottom = (int)(rect.y + rect.h) / ts;
            for (int x = startX; x <= endX; x++) {
                if (tileMap.IsSolid(x, rowBottom)) {
                    rect.y = rowBottom * ts - rect.h;
                    velocityY = 0;
                    isGrounded = true;
                    break;
                }
            }
        }
        else if (velocityY < 0) {
            int rowTop = py / ts;
            for (int x = startX; x <= endX; x++) {
                if (tileMap.IsSolid(x, rowTop)) {
                    rect.y = (rowTop + 1) * ts;
                    velocityY = 0;
                    break;
                }
            }
        }
    }
}