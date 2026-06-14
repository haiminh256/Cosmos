#include <Engine.h>
#include <Engine/TileMap.h>
#include <random>
#include <Engine/Audio.h>
#include "Player.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(0,2);
int levelIndex = distr(gen);

std::vector<std::vector<int>> level0 = {
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3}, 
    {3,3,3,3,3,3,3,3,2,2,2,2,2,2}, 
    {3,3,3,3,3,3,2,3,3,3,3,3,3,3}, 
    {3,3,3,2,3,3,3,3,3,3,3,3,3,3},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,2,2,2,3,3,3,3,3,3,3,3,3}, 
    {3,3,3,3,3,3,2,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,2,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,2,3,3,3},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

std::vector<std::vector<int>> level1 = {
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // Hàng 0 - ĐÍCH (Góc phải trên cùng)
    {3,3,3,3,3,3,3,3,3,3,3,2,2,2}, // Hàng 1 - Bục cuối cùng để chạm đích
    {3,3,3,3,3,3,3,3,2,2,2,3,3,3}, // Hàng 2
    {3,3,3,3,3,2,2,3,3,3,3,3,3,3}, // Hàng 3 - Bục trung chuyển hướng sang phải
    {2,2,2,3,3,3,3,3,3,3,3,3,3,3}, // Hàng 4 - Nhảy ngược về bên trái
    {3,3,3,3,2,2,3,3,3,3,3,3,3,3}, // Hàng 5
    {3,3,3,3,3,3,3,2,2,3,3,3,3,3}, // Hàng 6 - Bục đầu tiên khi từ sàn nhảy lên
    {3,3,3,3,3,3,3,3,3,3,2,2,3,3}, // Hàng 7
    {3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Hàng 8
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1}  // Hàng 9 - Vực thẳm ở giữa sàn! Rơi xuống là qua màn/reset
};
std::vector<std::vector<int>> level2 = {
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3}, // Hàng 0 - ĐÍCH (Góc phải trên cùng)
    {3,3,3,3,3,3,3,3,3,3,3,3,2,2}, // Hàng 1 - Bục đích
    {3,3,3,3,3,3,3,3,3,2,2,3,3,3}, // Hàng 2
    {3,3,3,3,3,3,2,2,3,3,3,3,3,3}, // Hàng 3
    {3,2,3,3,3,3,3,3,3,3,3,3,3,3}, // Hàng 4 - Các bục đá nhỏ dẫn lên
    {3,2,2,3,3,3,3,3,3,3,3,3,3,3}, // Hàng 5
    {3,3,3,3,3,2,2,3,3,3,3,3,3,3}, // Hàng 6 - Bục nhảy dài để lấy đà
    {3,3,3,3,3,3,3,3,3,2,2,3,3,3}, // Hàng 7
    {3,3,3,3,3,3,3,3,3,3,3,3,2,2}, // Hàng 8 - Vị trí xuất phát an toàn (100, 100) sẽ rơi trúng bục này
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1}  // Hàng 9 - Toàn bộ sàn biến thành VỰC THẲM!
};
 
int main(int argc, char* argv[]) {
    Cosmos::Engine App;
    App.Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO);
    App.CreateAppWindow("Jumping Hoshino", 896, 640);
    App.CreateRenderer();
    App.UseVsync();
    App.Log("main() EntryPoint successs", "INFO");

    Cosmos::Audio audioManager;
    audioManager.PlayBGM("res/sfx/UsagiFlap.mp3");

    Player player(100.0f, 100.0f); 
    Cosmos::Texture playerTexture;
    playerTexture.Load(App.GetRenderer(), "res/hoshino.png");
    player.SetTexture(&playerTexture);
    player.SetAudio(&audioManager);

    Cosmos::TileMap map(64);
    Cosmos::Texture tileTexture;
    tileTexture.Load(App.GetRenderer(), "res/map.png");
    map.SetTexture(&tileTexture);
    
    player.SetTileMap(&map);

    map.LoadFromCSV("res/level0.csv");
    while(App.IsRunning()){
        App.EventHandle();
        App.UpdateDeltaTime();
        
        player.Update(App.GetDeltaTime());
        App.ShowFPS();
        
        
        if (player.HasReachedNextLevel() == true) {
            levelIndex++;
            
            if (levelIndex == 1) {
                map.Load(level1); 
            } 
            else if (levelIndex == 2) {
                map.Load(level2); 
            }
            else {
                levelIndex = 0;
                map.LoadFromCSV("res/level0.csv");
            }

        player.Respawn(100.0f, 100.0f);
    }

        App.Clear();
        
        map.Render(App.GetRenderer());
        player.Render(App.GetRenderer());

        App.Present();
    }

    App.Quit();
    return 0;
}
