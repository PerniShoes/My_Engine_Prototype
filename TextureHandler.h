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

class TextureHandler
{
public:

	TextureHandler();
	~TextureHandler();

	TextureHandler(const TextureHandler&) = delete;
	TextureHandler& operator = (const TextureHandler&) = delete;

	typedef enum
	{
		Background = 0,
		Foo = 1,
		MainText = 2,

		TotalTextures = 3

	}TextureList;


	//void render(SDL_Point pos, SDL_Rect* clip = NULL);
	
	void setColor(int textureId, SDL_Color color);
	void setAlpha(int textureId, Uint8 alpha);
	void setBlendMode(int textureId, SDL_BlendMode blendMode);


	void setScale(int textureId, float ratio = 1.0f);
	void setFlip(int textureId, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void setRotate(int textureId, double angle = 0.0, SDL_Point* center = NULL);

	// PDN  TTF_Font* getFont(int textureId);

	SDL_Rect getRect(int textureId);
	void setPos(int x, int y); // SDL_Point maybe
	


//	void RenderFromStruct(SDL_My_Texture& texture, m_Texture& textureStruct);

	
	//

	//animation
	//static const int M_WALKING_ANIMATION_FRAMES = 4;
	//SDL_Rect m_WalkingSpriteClips[M_WALKING_ANIMATION_FRAMES];


	void render(int textureId);

	void loadTextures();
private:

	bool loadFromFile(const	std::string& path, int colorKeyFlag = 1, SDL_Color colorKey = SDL_Color{255,255,255});	
	bool loadFromRenderedText(const std::string& textureText);





	// Done
		
	void initText(int textureId, const char* text, int ptSize = 24, SDL_Color color = { 255, 255, 255 });

	//SDL_Surface*& createSurface(const char* &texturePaths, int textureId);	
	void createTextureFromSurface(const char* texturePaths,int textureId);

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

	TextureProperties m_TextureProperties[TotalTextures]{};
	SDL_Texture* m_Texture[TotalTextures]{};		


};

