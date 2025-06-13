#pragma once // NOLINT
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "Debug.h"

enum class SoundsList
{
	ScratchSound = 0,
	HighSound = 1,
	MediumSound = 2,
	LowSound = 3,

	TotalSounds = 4

};

enum class MusicList
{
	StopMusic = -2,
	PauseOrResume = -1,

	DefaultMusic = 0,
	HolyF = 1,
	Pandemonium = 2,
	GimmeLove = 3,
	AreYouGonnaBeMyGirl = 4,
	WezPigulke = 5,
	ALittleMessedUp = 6,
	BeautifulMadness = 7,
	ImComing = 8,
	ThatsWhatILike = 9,
	Gold = 10,
	Hold = 11,


	TotalMusic = 12
};

using enum MusicList;
using enum SoundsList;


class Audio
{
public:


	Audio();
	~Audio();

	Audio(const Audio&) = delete;
	Audio& operator = (const Audio&) = delete;


	bool LoadAudio();
	void PlaySound(SoundsList soundId, int loopAmount = 0, int channel = -1)const;
	void PlayMusic(MusicList musicId, int loopAmount = 10);


	struct VolumeList
	{

		const int DefaultMusic = 16;
		const int HolyF = 48;
		const int Pandemonium = 16;
		const int GimmeLove = 32;
		const int AreYouGonnaBeMyGirl = 88;
		const int WezPigulke = 32;
		const int ALittleMessedUp = 32;
		const int BeautifulMadness = 64;
		const int ImComing = 32;
		const int ThatsWhatILike = 48; 
		const int Gold = 32;
		const int Hold = 32;

	}m_Volume;


private:

	void AdjustVolume(int musicId) const;
	void SetPaths();
	bool LoadWAV(Mix_Chunk*& soundStorage, const std::string& path);
	bool LoadMusic(Mix_Music*& musicStorage, const std::string& path);
	void Free();

	Mix_Chunk* m_Sound[(int)SoundsList::TotalSounds]{};	
	const char* m_SoundPath[(int)TotalSounds]{};

	Mix_Music* m_Music[(int)MusicList::TotalMusic]{};		
	const char* m_MusicPath[(int)TotalMusic]{};	

};

