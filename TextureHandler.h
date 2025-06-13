#pragma once // NOLINT
#include <string>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Window.h"
#include "Renderer.h"
#include "Debug.h"

	// Just hold all the textures here and then if I want to change one I will call Function(textureId, arg);
	// Most of the code can be reused, I just need to implement the usage of an array with all of the textures

	// I can also have functions like: renderALL(); setAlphaAll(); setRotateALL(); If I wanted to apply something to all of them at once, 
	// like just reseting to default or spinning the whole scene or making the whole scene bright/dark or w/e
	// 
	// 
	// Or if feeling fancy (DON'T xD!) I could have things like setAlphaMany(textureId listOfIds); to apply something to many at once


enum class TextureList
{
	Background = 0,
	Foo = 1,
	MainText = 2,
	FuckEverything = 3,
	Hero = 4,

	TotalTextures = 5
	
};

using enum TextureList;

class TextureHandler
{
public:

	TextureHandler();
	~TextureHandler();

	TextureHandler(const TextureHandler&) = delete;
	TextureHandler& operator = (const TextureHandler&) = delete;

	/* PDN:
	
	TTF_Font* getFont(int textureId);

	SDL_Rect getRect(int textureId);
	*/

	//

	//animation
	//static const int M_WALKING_ANIMATION_FRAMES = 4;
	//SDL_Rect m_WalkingSpriteClips[M_WALKING_ANIMATION_FRAMES];

	//Done
	bool loadTextures();
	void setClip(TextureList textureId, SDL_Rect* clip = NULL);
	void render(TextureList textureId) const;
	void setPos(TextureList textureId, SDL_Point currentPos = SDL_Point{ 0,0 }, SDL_Point change = SDL_Point{ 0,0 });
	void transform(TextureList textureId, 
		float scale = 1.0f, SDL_RendererFlip flipType = SDL_FLIP_NONE, 
		double angle = 0.0, SDL_Point* center = NULL);


	void setScaleAll(float ratio = 1.0f);
	void setScale(TextureList textureId, float ratio = 1.0f);
	void setColor(TextureList textureId, SDL_Color color) const;
	void setAlpha(TextureList textureId, Uint8 alpha) const;
	void setBlendMode(TextureList textureId, SDL_BlendMode blendMode) const;

	void setFlip(TextureList textureId, SDL_RendererFlip flipType = SDL_FLIP_NONE);
	void setRotate(TextureList textureId, double angle = 0.0, SDL_Point* center = NULL);

private:

	// Done
		
	void initText(TextureList textureId, const char* text, int ptSize = 24, SDL_Color color = { 255, 255, 255 });
	bool createTextureFromSurface(const char* texturePaths, TextureList textureId);
	void freeResources();

	struct TextureProperties
	{
		// Base propeties
		SDL_Rect m_Rect;
		float m_Scale;	
		SDL_Rect* m_Clip;
		
		// Orientation
		SDL_Point* m_RotationCenter;
		double m_RotationDegrees;
		SDL_RendererFlip m_FlipType;

		// Colors
		SDL_Color m_Color;
		Uint8 m_Alpha;

		// Animation 
		int m_FrameSlow;
		SDL_Rect* m_CurrentClip;
		int m_CurrentFrame;

		// Text
		bool m_IsText;
		TTF_Font* m_Font;
		const char* m_Text;
		int m_PtSize;

	};	

	TextureProperties m_TextureProperties[static_cast<int>(TotalTextures)]{};
	SDL_Texture* m_Texture[static_cast<int>(TotalTextures)]{};


};

