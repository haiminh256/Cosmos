#include <Engine/Log.h>
#include <Engine.h>

namespace Cosmos {
    Engine::Engine(){
        window = nullptr;
        renderer = nullptr;
        isRunning = true;
        frameCount = 0;
        lastFPSTime = 0;
    }
    void Engine::Init(SDL_InitFlags flags){
        if(!SDL_Init(flags)){
            CORE_ERROR("Engine::Init() failed");
        }
        if(!MIX_Init()){
            CORE_ERROR("Engine::Init() failed");
        }
        Logger::Init();
        CORE_INFO("Engine::Init() success");
    }
    void Engine::CreateAppWindow(const char* title, int width, int height){
        window = SDL_CreateWindow(title, width, height, SDL_WINDOW_BORDERLESS);
        if(!window){
            CORE_ERROR("Engine::CreateWindow() failed");
        }
        CORE_INFO("Engine::CreateWindow() success");
    }
    void Engine::CreateRenderer(){
        renderer = SDL_CreateRenderer(window, nullptr);
        if(!renderer){
            CORE_ERROR("Engine::CreateRenderer() failed");
        }
        CORE_INFO("Engine::CreateRenderer() success");
    }
    void Engine::ShowFPS()
    {
        frameCount++;

        Uint64 currentTime = SDL_GetTicks();

        if(currentTime - lastFPSTime >= 10000)
        {
            float fps =
                frameCount * 1000.0f /
                (currentTime - lastFPSTime);

            CORE_INFO(
                "Engine::ShowFPS() FPS: {}",
                (int)fps
            );

            frameCount = 0;
            lastFPSTime = currentTime;
        }
    }
    void Engine::UseVsync(){
        SDL_SetRenderVSync(renderer, 1);
        CORE_INFO("Engine::UseVSync success");
    }   
    bool Engine::IsRunning() const {
        return isRunning;
    }
    void Engine::UpdateDeltaTime() {
        Uint64 currentTime = SDL_GetTicks();

        deltaTime =
            (currentTime - lastFrameTime) / 1000.0f;

        lastFrameTime = currentTime;
    }
    float Engine::GetDeltaTime() const {
        return deltaTime;
    }
    void Engine::EventHandle(){
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_EVENT_QUIT){
                isRunning = false;
            }
        }
    }
    void Engine::Log(std::string content, std::string logLevel){
        CORE_INFO(content);
    }
    void Engine::Quit(){
        SDL_Quit();
        CORE_INFO("Engine::Quit() success");
    }
    SDL_Renderer* Engine::GetRenderer(){
        return renderer;
    }
    void Engine::Clear(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    void Engine::Present(){
        SDL_RenderPresent(renderer);
    }
}
