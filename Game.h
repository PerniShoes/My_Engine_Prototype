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
#include "SDL_My_Texture.h"
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

		void ModifyTexture(SDL_My_Texture& texture, float scale = 1.0f, SDL_RendererFlip flipType = SDL_FLIP_NONE, double angle = 0.0, SDL_Point* center = NULL);	

		struct m_Texture
		{
			SDL_Point pos;
			SDL_Point* rotationCenter;
			double rotationDegrees;
			SDL_RendererFlip flipType;
			SDL_Color color;
			float scale;
			Uint8 alpha;

			// animation for now:
			int frameSlow; // Need a better name
			SDL_Rect* currentClip;
			int currentFrame;
		};
		
		int m_TestInt;

		void RenderFromStruct(SDL_My_Texture& texture, m_Texture& textureStruct);

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
		

		m_Texture m_BackgroundTextureProp;
		SDL_My_Texture m_BackgroundTexture;

		m_Texture m_FooAnimatedTextureProp;
		SDL_My_Texture m_FooAnimatedTexture;

		m_Texture m_TestTextTextureProp;
		SDL_My_Texture m_TestTextTexture;


		//animation
		static const int M_WALKING_ANIMATION_FRAMES = 4;
		SDL_Rect m_WalkingSpriteClips[M_WALKING_ANIMATION_FRAMES];
};