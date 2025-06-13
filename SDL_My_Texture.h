#pragma once // NOLINT
#include <string>
#include <cmath>
#include <SDL.h>
#include <Debug.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "Renderer.h"


class SDL_My_Texture
{

	public:
		SDL_My_Texture();
		~SDL_My_Texture();


		bool loadFromFile(const	std::string& path, int colorKey = 1);	
		bool loadFromRenderedText(const std::string& textureText);
	
		void render(SDL_Point pos, SDL_Rect* clip = NULL);
		void setColor(SDL_Color color);
		void setAlpha(Uint8 alpha);
		void setBlendMode(SDL_BlendMode blendMode);

		void scale(float ratio = 1.0f);
		void flip(SDL_RendererFlip flip = SDL_FLIP_NONE);
		void rotate(double angle = 0.0, SDL_Point* center = NULL);
	
		void setFont(TTF_Font* font);
		TTF_Font* getFont();

		int getWidth();
		int getHeight();
	private:

		void freeResources();
		//Lazy foo
		SDL_Texture* m_Texture;
		int m_Width;
		int m_Height;

		//Yours trully (me)
		float m_ScaleRatio;
		double m_Angle;
		SDL_Point* m_Center;
		SDL_RendererFlip m_Flip;

		TTF_Font* m_Font;

};

