#include "Player.h"
#include <Engine/Audio.h>

Player::Player(float x, float y)
    : speed(300.0f),
      gravity(1000.0f),
      jumpForce(-498.0f),
      reachedNextLevel(false),
      currentMap(nullptr)
      
{
    rect = {x, y, 64.0f, 64.0f};
    velocityX = 0.0f;
    velocityY = 0.0f;
    isGrounded = false;
}

void Player::Update(float dt)
{
    HandleInput(dt);
    rect.x += velocityX * dt;
    if (currentMap != nullptr) {
        CheckMapCollisionX(*currentMap);
    }
    velocityY += gravity * dt;
    rect.y += velocityY * dt;
    
    isGrounded = false; 
    if (currentMap != nullptr) {
        CheckMapCollisionY(*currentMap);
    }
    if (rect.y > 512.0f) {
        rect.y = 512.0f;
        velocityY = 0.0f;
        isGrounded = true;
    }
    if (rect.x < 0) rect.x = 0;
    if (rect.x + rect.w > 896.0f) rect.x = 896.0f - rect.w;
    if (rect.y < 0) {
        rect.y = 0;
        velocityY = 0;
    }

    if ((rect.x + rect.w >= 896.0f) && (rect.y <= 64.0f)) 
    {
        this->reachedNextLevel = true; 
    }
}

void Player::HandleInput(float dt)
{
    const bool* keys = SDL_GetKeyboardState(nullptr);
    if (!keys) return;

    velocityX = 0.0f;

    if (keys[SDL_SCANCODE_A]) velocityX = -speed;
    if (keys[SDL_SCANCODE_D]) velocityX = speed;
    if (keys[SDL_SCANCODE_M]) audioManager->StopBGM();
    if (keys[SDL_SCANCODE_SPACE] && isGrounded)
    {
        velocityY = jumpForce;
        isGrounded = false;
        if (audioManager != nullptr) {
            audioManager->PlaySFX("../res/sfx/jump.mp3");
        }
    }
}
float Player::GetX(){
    return x;
}
float Player::GetY(){
    return y;
}
void Player::SetX(float x){
    rect.x = x;
}
void Player::SetY(float y){
    rect.y = y;
}
void Player::Respawn(float spawnX, float spawnY)
{
    rect.x = spawnX;
    rect.y = spawnY;  
    
    velocityX = 0.0f;
    velocityY = 0.0f;   
    isGrounded = false;

    reachedNextLevel = false; 
}