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
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,2,2,2},
    {3,3,3,3,3,3,3,3,2,2,2,3,3,3},
    {3,3,3,3,3,2,2,3,3,3,3,3,3,3},
    {2,2,2,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,2,2,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,2,2,3,3,3,3,3}, 
    {3,3,3,3,3,3,3,3,3,3,2,2,3,3}, 
    {3,3,3,3,3,3,3,3,3,3,3,3,3,2}, 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1} 
};
std::vector<std::vector<int>> level2 = {
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3}, 
    {3,3,3,3,3,3,3,3,3,3,3,3,2,2}, 
    {3,3,3,3,3,3,3,3,3,2,2,3,3,3},
    {3,3,3,3,3,3,2,2,3,3,3,3,3,3}, 
    {3,2,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,2,2,3,3,3,3,3,3,3,3,3,3,3},
    {3,3,3,3,3,2,2,3,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,3,3,2,2,3,3,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,2,2}, 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1} 
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

    map.Load(level0);

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
                map.Load(level0);
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
