#pragma once

#include <Engine/Entity.h>
#include <Engine/Audio.h>

class Player : public Entity {
public:
    Player(float x, float y);

    // Override hàm thuần ảo Update từ Entity cha
    void Update(float dt) override;

    // Các hàm quản lý chuyển level phụ trợ cho main.cpp
    bool HasReachedNextLevel() const { return reachedNextLevel; }
    void ResetLevelFlag() { reachedNextLevel = false; }
    void ResetVelocity() {     velocityX = 0.0f;   velocityY = 0.0f;  isGrounded = false;}
    void SetTileMap(TileMap* map) { currentMap = map; }
    float GetX();
    float GetY();
    void SetX(float x);
    void SetY(float y);
    void Respawn(float spawnX, float spawnY);
    void SetAudio(Audio* audio) { audioManager = audio; }
private:
    void HandleInput(float dt);

private:
    Audio* audioManager = nullptr;
    float speed;
    float gravity;
    float jumpForce;
    float x, y;
    bool reachedNextLevel;
    TileMap* currentMap; // Lưu con trỏ bản đồ để truyền vào hàm va chạm của cha
};