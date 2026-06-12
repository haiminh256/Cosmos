#include "Player.h"
#include <Engine/Audio.h>

Player::Player(float x, float y)
    : speed(300.0f),
      gravity(1000.0f),
      jumpForce(-498.0f),
      reachedNextLevel(false),
      currentMap(nullptr)
      
{
    // rect, velocityX, velocityY, isGrounded được kế thừa từ lớp cha Entity
    rect = {x, y, 64.0f, 64.0f};
    velocityX = 0.0f;
    velocityY = 0.0f;
    isGrounded = false;
}

void Player::Update(float dt)
{
    HandleInput(dt);
    
    // 1. Xử lý trục X (Gọi hàm va chạm từ Entity cha)
    rect.x += velocityX * dt;
    if (currentMap != nullptr) {
        CheckMapCollisionX(*currentMap);
    }

    // 2. Xử lý trục Y (Gọi hàm va chạm từ Entity cha)
    velocityY += gravity * dt;
    rect.y += velocityY * dt;
    
    isGrounded = false; 
    if (currentMap != nullptr) {
        CheckMapCollisionY(*currentMap);
    }

    // ==========================================================
    // KHÓA BIÊN AN TOÀN CHO MÀN HÌNH 896x640
    // ==========================================================
    // Đứng vững trên sàn cỏ hàng số 9 (y = 512)
    if (rect.y > 512.0f) {
        rect.y = 512.0f;
        velocityY = 0.0f;
        isGrounded = true;
    }

    // Giới hạn biên không cho đi lùi ra ngoài màn hình
    if (rect.x < 0) rect.x = 0;
    if (rect.x + rect.w > 896.0f) rect.x = 896.0f - rect.w;
    if (rect.y < 0) {
        rect.y = 0;
        velocityY = 0;
    }

    // ==========================================================
    // ĐIỀU KIỆN CHUYỂN LEVEL: CHẠM VÀO GÓC TRÊN CÙNG BÊN PHẢI
    // ==========================================================
    // Nhân vật rộng 64px, cao 64px. 
    // Khi chạm góc phải trên cùng: rect.x + rect.w đạt sát biên 896 và rect.y nằm ở hàng 0 (dưới 64px)
    if ((rect.x + rect.w >= 896.0f) && (rect.y <= 64.0f)) 
    {
        this->reachedNextLevel = true; 
    }
}

void Player::HandleInput(float dt)
{
    const bool* keys = SDL_GetKeyboardState(nullptr);
    if (!keys) return;

    velocityX = 0.0f; // Reset vận tốc ngang mỗi khung hình

    if (keys[SDL_SCANCODE_A]) velocityX = -speed;
    if (keys[SDL_SCANCODE_D]) velocityX = speed;

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
    rect.x = spawnX;    // Đưa vị trí X của hộp va chạm về điểm hồi sinh
    rect.y = spawnY;    // Đưa vị trí Y của hộp va chạm về điểm hồi sinh
    
    velocityX = 0.0f;   // Triệt tiêu vận tốc ngang
    velocityY = 0.0f;   // Triệt tiêu lực rơi/lực nhảy
    isGrounded = false; // Trạng thái lơ lửng để rơi tự do xuống gạch mới

    reachedNextLevel = false; // Hạ cờ hiệu chuyển màn xuống (ResetLevelFlag)
}