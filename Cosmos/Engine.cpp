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
            Engine_Log("Engine::Init() failed", "ERROR");
        }
        if(!MIX_Init()){
            Engine_Log("Engine::Init() failed", "ERROR");
        }
        Engine_Log("Engine::Init() success", "INFO");
    }
    void Engine::CreateWindow(const char* title, int width, int height){
        window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
        if(!window){
            Engine_Log("Engine::CreateWindow() failed", "ERROR");
        }
        Engine_Log("Engine::CreateWindow() success", "INFO");
    }
    void Engine::CreateRenderer(){
        renderer = SDL_CreateRenderer(window, nullptr);
        if(!renderer){
            Engine_Log("Engine::CreateRenderer() failed", "ERROR");
        }
        Engine_Log("Engine::CreateRenderer() success", "INFO");
    }
    void Engine::ShowFPS()
    {
        frameCount++;

        Uint64 currentTime = SDL_GetTicks();

        if(currentTime - lastFPSTime >= 5000)
        {
            float fps =
                frameCount * 1000.0f /
                (currentTime - lastFPSTime);

            Engine_Log(
                "Engine::ShowFPS() FPS: " + std::to_string((int)fps),
                "INFO"
            );

            frameCount = 0;
            lastFPSTime = currentTime;
        }
    }
    void Engine::UseVsync(){
        SDL_SetRenderVSync(renderer, 1);
        Engine_Log("Engine::UseVSync success", "INFO");
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
        std::cout << "[" << logLevel << "]" << ":" << " " << content << std::endl;
    }
    void Engine::Quit(){
        SDL_Quit();
        Engine_Log("Engine::Quit() success", "INFO");
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