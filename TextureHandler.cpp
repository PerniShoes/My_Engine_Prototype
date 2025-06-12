#include "TextureHandler.h"

TextureHandler::TextureHandler()
{
	
};

TextureHandler::~TextureHandler()
{

};

void TextureHandler::setPos(int x, int y)
{

};

void TextureHandler::initText(int textureId, const char* text, int ptSize, SDL_Color color)
{
	m_TextureProperties[textureId].m_IsText = true;
	m_TextureProperties[textureId].m_Text = text;	
	m_TextureProperties[textureId].m_PtSize = ptSize;	
	m_TextureProperties[textureId].m_Color = color;	
};

void TextureHandler::loadTextures()		
{
	const char* texturePaths[TotalTextures]{};
	texturePaths[Background] = "Images/background.png";
	texturePaths[Foo] = "Images/foo_animated.png";

	texturePaths[MainText] = "Fonts/lazy.ttf";
	initText(MainText, "THIS IS MADNESS");	



	/*for (int index{ 0 }; index < TotalTextures; index++)
	{
		createTextureFromSurface(texturePaths[index], index);
	}*/

	createTextureFromSurface(texturePaths[Foo],Foo);	

};

void TextureHandler::createTextureFromSurface(const char* texturePaths, int textureId)
{
	SDL_Surface* surface = IMG_Load("Images/foo_animated.png");

	//if (m_TextureProperties[textureId].m_IsText)
	//{
	//	surface = TTF_RenderText_Solid(TTF_OpenFont(texturePaths, m_TextureProperties[textureId].m_PtSize),
	//		m_TextureProperties[textureId].m_Text, m_TextureProperties[textureId].m_Color);

	//	if (surface == NULL)
	//	{
	//		Debug::Print("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	//	}
	//}
	//else
	//{
	//	surface = IMG_Load(texturePaths);

	//	if (surface == NULL)
	//	{
	//		Debug::Print("Unable to load image from file %! SDL_image Error: %s ", IMG_GetError(), "\n");
	//	}
	//	
	//}

	m_Texture[textureId] = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), surface);
	if (m_Texture[textureId] == NULL)		
	{
		Debug::Print("Unable to create Texture from Surface, textureId: ", textureId, " SDL Error: %s\n", SDL_GetError());
	}
	else
		{
		m_TextureProperties[textureId].m_Rect.w = surface->w;		
		m_TextureProperties[textureId].m_Rect.h = surface->h;
		}

	SDL_FreeSurface(surface);

}

//SDL_Surface*& TextureHandler::createSurface(const char* &texturePaths, int textureId) 	
//{
//	if (m_TextureProperties[textureId].m_IsText)	
//	{
//		SDL_Surface* textSurface = TTF_RenderText_Solid(TTF_OpenFont(texturePaths, m_TextureProperties[textureId].m_PtSize),	
//		m_TextureProperties[textureId].m_Text, m_TextureProperties[textureId].m_Color);	
//		
//		if (textSurface == NULL)
//		{
//			Debug::Print("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
//		}
//		return textSurface;	
//
//	}
//	else 
//	{
//		SDL_Surface* fileSurface = IMG_Load(texturePaths);
//
//		if (fileSurface == NULL)	
//		{
//			Debug::Print("Unable to load image from file %! SDL_image Error: %s ", IMG_GetError(), "\n");
//		}
//		return fileSurface;
//	}
//	
//}

void TextureHandler::freeResources()
{
	for (int index{ 0 }; index < TotalTextures; index++)	
	{
		if (m_TextureProperties[index].m_IsText)
		{
			TTF_CloseFont(m_TextureProperties[index].m_Font);
			m_TextureProperties[index].m_Font = NULL;	

			SDL_DestroyTexture(m_Texture[index]);
			m_Texture[index] = NULL;	
		}
		else
		{
			SDL_DestroyTexture(m_Texture[index]);
			m_Texture[index] = NULL;	
		}
	}
}

void TextureHandler::render(int textureId)	
{
	
	if (m_TextureProperties[textureId].m_Clip != NULL)
	{
		m_TextureProperties[textureId].m_Rect.w = int(m_TextureProperties[textureId].m_Clip->w * m_TextureProperties[textureId].m_Scale);	
		m_TextureProperties[textureId].m_Rect.h = int(m_TextureProperties[textureId].m_Clip->h * m_TextureProperties[textureId].m_Scale);	
	}
	
	SDL_RenderCopyEx(
		Renderer::GetRenderer(), m_Texture[textureId],

		m_TextureProperties[textureId].m_Clip, 
		&m_TextureProperties[textureId].m_Rect,		
		m_TextureProperties[textureId].m_RotationDegrees, 
		m_TextureProperties[textureId].m_RotationCenter,
		m_TextureProperties[textureId].m_FlipType);
		
}
