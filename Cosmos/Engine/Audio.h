#pragma once

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <EngineEnv.h>
namespace Cosmos {
    class COSMOS_API Audio {
    public:
        Audio();
        ~Audio();


        void PlaySFX(const std::string& filePath);


        void PlayBGM(const std::string& filePath);
        

        void StopBGM();

    private:
        MIX_Mixer* m_mixer;    
        MIX_Track* m_bgmTrack;   
        MIX_Audio* m_bgmAudio; 
    };
}