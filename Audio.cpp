#include "Audio.h"
Audio::Audio()
{
    SetPaths();

};

Audio::~Audio()
{
    Free();
    Mix_Quit();
};

void Audio::SetPaths()
{
    m_SoundPath[Scratch] = "Audio/Sounds/scratch.wav"; 
    m_SoundPath[High] = "Audio/Sounds/high.wav";   
    m_SoundPath[Medium] = "Audio/Sounds/medium.wav";   
    m_SoundPath[Low] = "Audio/Sounds/low.wav";   

    m_MusicPath[DefaultMusic] = "Audio/Music/beat.wav";   
    m_MusicPath[HolyF] = "Audio/Music/HolyFuck.mp3";  
    m_MusicPath[Pandemonium] = "Audio/Music/Pandemonium.mp3";
    m_MusicPath[GimmeLove] = "Audio/Music/GimmeLove.mp3";
    m_MusicPath[AreYouGonnaBeMyGirl] = "Audio/Music/AreYouGonnaBeMyGirl.mp3";
    m_MusicPath[WezPigulke] = "Audio/Music/WezPigulke.mp3";
    m_MusicPath[Gold] = "Audio/Music/Gold.mp3";
    m_MusicPath[ThatsWhatILike] = "Audio/Music/ThatsWhatILike.mp3";
    m_MusicPath[ImComing] = "Audio/Music/ImComing.mp3";
    m_MusicPath[Hold] = "Audio/Music/Hold.mp3";
    m_MusicPath[BeautifulMadness] = "Audio/Music/BeautifulMadness.mp3";
    m_MusicPath[ALittleMessedUp] = "Audio/Music/ALittleMessedUp.mp3";

};

void Audio::PlaySound(int soundId, int loopAmount, int channel) const
{
    Mix_MasterVolume(15);

    if (soundId >= TotalSounds || soundId < 0)
    {
        Debug::Print("Incorrect soundId \n");
    }
    else
    {
    Mix_PlayChannel(channel, m_Sound[soundId], loopAmount);
    }

};

void Audio::PlayMusic(int musicId, int loopAmount) 
{
    if (musicId >= TotalMusic || musicId < -2)
    {
        Debug::Print("Incorrect musicId \n");
    }
    else if (musicId == Stop)
    {
       Mix_HaltMusic();
    }
    else if (musicId == PauseOrResume)
    {
        if (Mix_PausedMusic())
        {
            Mix_ResumeMusic();
        }
        else
        {
            Mix_PauseMusic();
        }
    }
    else if(!Mix_PlayingMusic())
    {
        Mix_PlayMusic(m_Music[musicId], loopAmount);
        AdjustVolume(musicId);
    }
     
};

void Audio::Free()
{
    for (int i{ 0 }; i < TotalSounds; i++)
    {
        Mix_FreeChunk(m_Sound[i]);
        m_Sound[i] = NULL; 
    };
    
    for (int i{ 0 }; i < TotalMusic; i++)
    {
        Mix_FreeMusic(m_Music[i]);
        m_Music[i] = NULL;
    };

};

bool Audio::LoadWAV(Mix_Chunk* &soundStorage, const std::string& path) 
{   
    bool success = true;
    soundStorage = Mix_LoadWAV(path.c_str());   
    if (soundStorage == NULL)   
    {
        Debug::Print("Failed to load ", path ," sound effect! SDL_mixer Error: %s ", Mix_GetError(), "\n");
        success = false;
    }
    return success;
};

bool Audio::LoadMusic(Mix_Music* &musicStorage, const std::string& path)
{
    bool success = true;
    musicStorage = Mix_LoadMUS(path.c_str());
    if (musicStorage == NULL)
    {
        Debug::Print("Failed to load ", path, " music! SDL_mixer Error: %s ", Mix_GetError(), "\n");
        success = false;
    }
    return success;

};

void Audio::AdjustVolume(int musicId) const
{
    switch (musicId)
    {
    case 0:
        Mix_VolumeMusic(m_Volume.DefaultMusic); 
        break;
    case 1:
        Mix_VolumeMusic(m_Volume.HolyF);    
        break;  
    case 2:
        Mix_VolumeMusic(m_Volume.Pandemonium);
        break;
    case 3:
        Mix_VolumeMusic(m_Volume.GimmeLove);
        break;
    case 4:
        Mix_VolumeMusic(m_Volume.AreYouGonnaBeMyGirl);
        break;
    case 5:
        Mix_VolumeMusic(m_Volume.WezPigulke);
        break;
    case 6:
        Mix_VolumeMusic(m_Volume.ALittleMessedUp);
        break;
    case 7:
        Mix_VolumeMusic(m_Volume.BeautifulMadness);
        break;
    case 8:
        Mix_VolumeMusic(m_Volume.ImComing);
        break;
    case 9:
        Mix_VolumeMusic(m_Volume.ThatsWhatILike);
        break;
    case 10:
        Mix_VolumeMusic(m_Volume.Gold);
        break;
    case 11:
        Mix_VolumeMusic(m_Volume.Hold);
        break;
    default:
        Mix_VolumeMusic(64);
    }


};

bool Audio::LoadAudio()
{
    bool success = true;

    for (int i{ 0 }; i < TotalSounds; i++)
    {
        LoadWAV(m_Sound[i], m_SoundPath[i]);
    }

    for (int i{ 0 }; i < TotalMusic; i++)
    {
        LoadMusic(m_Music[i], m_MusicPath[i]);
    }

    return success;
};
