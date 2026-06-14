#pragma once
#include <EngineEnv.h>

namespace Cosmos {
    class COSMOS_API Engine{
    public:
        Engine();
        void Init(SDL_InitFlags flags);
        void CreateAppWindow(const char* title, int width, int height);
        void CreateRenderer();
        void EventHandle();
        bool IsRunning() const;
        void UseVsync();
        void ShowFPS();
        void Quit();
        float GetDeltaTime() const;
        void Clear();
        void Present();
        void Log(std::string content, std::string logLevel);
        void UpdateDeltaTime();
        SDL_Renderer* GetRenderer();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event e;
        bool isRunning;
        Uint64 lastFPSTime;
        int frameCount;
        Uint64 lastFrameTime;
        float deltaTime;
    };
}