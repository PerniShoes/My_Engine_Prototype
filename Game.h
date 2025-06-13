#pragma once // NOLINT
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Window.h"

#include <stdio.h>
#include <string>
#include <cmath>

#include <Debug.h>
#include "Audio.h"
#include "TextureHandler.h"

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
	// GameInstance.

		Audio m_Audio;	
		TextureHandler m_Textures;

		void ObjectInit();
		void Events();
		void Logic();
		void Rendering();

		void HandleMouseEvents();
		void HandleKeyEvents();

		enum BackGroundSprite
		{
			MOUSE_OUT = 0,
			MOUSE_OVER_MOTION = 1,
			MOUSE_DOWN = 2,
			MOUSE_UP = 3,
			TOTAL = 4


		}m_BackgroundCheck;


		bool m_Quit;
		SDL_Event m_E;

		int m_MousePosX;
		int m_MousePosY;
		bool m_MouseInside;

		// Clean
		int m_Value;
		//
		
		//animation
		static const int M_WALKING_ANIMATION_FRAMES = 4;
		SDL_Rect m_WalkingSpriteClips[M_WALKING_ANIMATION_FRAMES];
};