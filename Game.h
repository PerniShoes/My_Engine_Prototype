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

		// Make self-contained
		int m_MousePosX;
		int m_MousePosY;
		bool m_MouseInside;
		//


		// Temp:
		int m_Speed; 
		SDL_Point m_PosChangeTemp;
		
	

		int whichFrame{ 0 };
		//
};