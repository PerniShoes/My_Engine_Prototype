#pragma once // NOLINT
#include <stdio.h>
#include <cmath>
#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Debug.h"
#include "Renderer.h"
#include "Window.h"
#include "Audio.h"
#include "TextureHandler.h"
#include "TimeHandler.h"
#include "Player.h"
#include "MouseHandler.h"
#include "Ball.h"
#include "EnemyAi.h"

enum class Gamemodes
{
	Vs_Ai = 0,
	Survival = 1,
	EndlessMadness = 2,

	TotalGamemodes = 3
};
using enum Gamemodes;

enum class PlatformColors
{
	almostTransparent = 0,
	Pwhite = 1,
	Pred = 2,
	Pblue = 3,
	Pgreen = 4,
	Pyellow = 5,
	Ppink = 6,
	Ppurple = 7,
	Porange = 8,
	PlightBlue = 9,

	TotalColors = 10
};
using enum PlatformColors;

class Game
{

	public:

		Game(const Game&) = delete;
		Game& operator = (const Game&) = delete;

		Game();	
	
		~Game();

		bool SDLInit();
		bool LoadMedia();
		void Close();

		void GameLoop();	
		
	private:
		// Game settings:
		Gamemodes m_Gamemode = Vs_Ai;		// Vs_Ai Survival EndlessMadness (EndlessMadness overwrites all other game settings)
		DifficultySettings m_AiDifficulty = DifficultySettings::veryHard; // easy medium hard veryHard unbeatable
		bool m_AiDiffIncreasing = false;    // Set to true to have Ai increase in difficulty with time, up to veryHard

		int m_ScoreToWin = 5;				// Anything up to 2 147 483 647 should work
		float m_BallSpeedIncrease = 1.05f;	// How much the ball speeds up on bounce (1.0f being none 1.05f being 5%)
		int m_BoardShrinkingSpeed = 0;		//Between 1-X (or more if you want insanity). 0 = Off

		// User settings:
		PlatformColors m_PlayerPlatformColor = PlightBlue; // Pwhite Pred Pblue Pgreen Pyellow Ppink Ppurple Porange PlightBlue almostTransparent
		int m_MusicVolume = 64;  // Between 0 (silence) and 128 (MAX)
		int m_SoundVolume = 128; // Between 0 (silence) and 128 (MAX)
		int m_ScreenBrightness = 100; // Between 0 (complete darkness) and 100 (default brightness)






		// Board borders:
		SDL_Rect m_BoardBorderTop;
		SDL_Rect m_BoardBorderBottom;
		SDL_Rect m_BoardBorderRightTest;
		int m_BorderGirth{ 300 };

		Audio m_Audio;	
		TextureHandler m_Textures;
		MouseHandler m_Mouse;
		TimeHandler m_Time;
		Player m_Player;
		Ball m_Ball;
		EnemyAi m_EnemyAi;

		void Events();
		void Logic();
		void Rendering();

		void HandleMouseEvents();
		void HandleKeyEvents();

		bool m_Quit;
		SDL_Event m_E;

		//Clean up
		enum BackGroundSprite
		{
			MOUSE_OUT = 0,
			MOUSE_OVER_MOTION = 1,
			MOUSE_DOWN = 2,
			MOUSE_UP = 3,
			TOTAL = 4

		}m_BackgroundCheck;
		//

		// Score handling:
		int m_SurvivalScore;
		int m_PlayerScore{ 0 };
		int m_AiScore{ 0 };
		void ballScoreHandling();


		// Showcase things:
		// Show different colors, different gamemodes, duh, survival end screen
		// Different screen size, different Ai difficulty, Ai difficulty adapting with score/time
		 
		// To write:
		void borderSizeHandling();

		
		// Some fluctuating number for border and player size shrinking on EndlessMadness
		// Also some number for normal border shrinking


		// Ball color changing with velocity, to more and more blue
		// Also add ball impact animations facing the way from which ball came 
		// Also can add impact on paddle but both might be bugged on high speeds
		// Can change which anim used based on speed
		


		//


		

		MusicList m_MusicPlaying;
		void handleMusic();



		// Temp:
		int m_Speed; 
		SDL_Point m_PosChangeTemp;
		
		float m_TempMult;

		int whichFrame{ 0 };
		//
};