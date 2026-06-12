#include <Engine/Audio.h>
#include <EngineEnv.h>
#include <iostream>

namespace Cosmos {
    void Audio::PlaySFX(const std::string& filePath) {
        if (!m_mixer) return;

        MIX_Audio* sfxAudio = MIX_LoadAudio(m_mixer, filePath.c_str(), false);
        
        if (!sfxAudio) {
            Engine_Log("Audio::PlaySFX PlaySFX failed: " + filePath + " " + SDL_GetError(), "ERROR");
        }
        Engine_Log("Audio::PlaySFX success: " + filePath, "INFO");


        MIX_PlayAudio(m_mixer, sfxAudio);
        MIX_DestroyAudio(sfxAudio);
    }

    void Audio::PlayBGM(const std::string& filePath) {
        if (!m_mixer) return;

        StopBGM(); 

        m_bgmAudio = MIX_LoadAudio(m_mixer, filePath.c_str(), false);
        if (!m_bgmAudio) {
            Engine_Log("Audio::PlayBGM failed: " + filePath + SDL_GetError(), "ERROR");
            return;
        }
        Engine_Log("Audio::PlayBGM success: " + filePath, "INFO");

        m_bgmTrack = MIX_CreateTrack(m_mixer);
        if (m_bgmTrack) {
            MIX_SetTrackAudio(m_bgmTrack, m_bgmAudio);
            

            SDL_PropertiesID props = SDL_CreateProperties();
            SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1); 
            

            MIX_PlayTrack(m_bgmTrack, props);
            
            SDL_DestroyProperties(props); 
        }
    }

    void Audio::StopBGM() {

        if (m_bgmTrack != nullptr) {  
            MIX_StopTrack(m_bgmTrack, 0);     
            m_bgmTrack = nullptr;          
        }
        

        if (m_bgmAudio != nullptr) {
            MIX_DestroyAudio(m_bgmAudio);
            m_bgmAudio = nullptr;          
        }
    }
    Audio::Audio() : m_mixer(nullptr), m_bgmTrack(nullptr), m_bgmAudio(nullptr) {
        if (!MIX_Init()) {
            Engine_Log("Audio::Audio constructor failed", "ERROR");
        }

        m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        if (!m_mixer) {
            Engine_Log("Audio::Audio MIX_CreateMixerDevice failed", "ERROR");
        }
    }


    Audio::~Audio() {
        StopBGM();
        MIX_Quit();
    }
}