#include "TextureHandler.h"


TextureHandler::TextureHandler()
{
	
};

TextureHandler::~TextureHandler()
{
	freeResources();
};

void TextureHandler::initText(TextureList textureId, const char* text, int ptSize, SDL_Color color)
{
	int textureIdInt = static_cast<int>(textureId);
	m_TextureProperties[textureIdInt].m_IsText = true;
	m_TextureProperties[textureIdInt].m_Text = text;	
	m_TextureProperties[textureIdInt].m_PtSize = ptSize;	
	m_TextureProperties[textureIdInt].m_Color = color;	
};

bool TextureHandler::loadTextures()		
{
	bool success = true;
	const char* texturePaths[static_cast<int>(TotalTextures)]{};
	// Images
	texturePaths[static_cast<int>(Background)] = "Images/background.png";
	texturePaths[static_cast<int>(Foo)] = "Images/foo_animated.png";
	texturePaths[static_cast<int>(FuckEverything)] = "Images/fuck_everything.png";
	texturePaths[static_cast<int>(Hero)] = "Images/Hero.bmp";


	// Fonts
	texturePaths[static_cast<int>(MainText)] = "Fonts/lazy.ttf";
	initText(MainText, "THIS IS MADNESS");	



	for (int index{ 0 }; index < static_cast<int>(TotalTextures); index++)
	{
	m_TextureProperties[index].m_Scale = 1.0f;
	success = createTextureFromSurface(texturePaths[index], static_cast<TextureList>(index));
	}

	return success;
};

void TextureHandler::setScaleAll(float ratio)
{
	for (int index{ 0 }; index < static_cast<int>(TotalTextures); index++)
	{
		m_TextureProperties[index].m_Scale = ratio;
		
	}
}

bool TextureHandler::createTextureFromSurface(const char* texturePaths, TextureList textureId)
{
	SDL_Surface* surface;
	bool success = true;
	int textureIdInt = static_cast<int>(textureId);

	if (m_TextureProperties[textureIdInt].m_IsText)
	{
		surface = TTF_RenderText_Solid(TTF_OpenFont(texturePaths, m_TextureProperties[textureIdInt].m_PtSize),
			m_TextureProperties[textureIdInt].m_Text, m_TextureProperties[textureIdInt].m_Color);

		if (surface == NULL)
		{
			Debug::Print("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
			return success;
		}
	}
	else
	{
		surface = IMG_Load(texturePaths);

		if (surface == NULL)
		{
			Debug::Print("Unable to load image from file %! SDL_image Error: %s ", IMG_GetError(), "\n");
			success = false;
			return success;
		}
		
	}

	m_Texture[textureIdInt] = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), surface);
	if (m_Texture[textureIdInt] == NULL)
	{
		Debug::Print("Unable to create Texture from Surface, textureId: ", textureIdInt, " SDL Error: %s\n", SDL_GetError());
		success = false;
		return success;
	}
	else
		{	
		m_TextureProperties[textureIdInt].m_Rect.w = surface->w;		
		m_TextureProperties[textureIdInt].m_Rect.h = surface->h;
		}

	SDL_FreeSurface(surface);
	return success;

}

void TextureHandler::freeResources()
{
	for (int index{ 0 }; index < (int)TotalTextures; index++)
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

void TextureHandler::render(TextureList textureId) const
{
	int textureIdInt = static_cast<int>(textureId);

	SDL_Rect renderQuad{ 
		m_TextureProperties[textureIdInt].m_Rect.x,
		m_TextureProperties[textureIdInt].m_Rect.y,
		int(m_TextureProperties[textureIdInt].m_Rect.w * m_TextureProperties[textureIdInt].m_Scale),
		int(m_TextureProperties[textureIdInt].m_Rect.h * m_TextureProperties[textureIdInt].m_Scale)};


	if (m_TextureProperties[textureIdInt].m_Clip != NULL)
	{
		renderQuad.w = int(m_TextureProperties[textureIdInt].m_Clip->w * m_TextureProperties[textureIdInt].m_Scale);
		renderQuad.h = int(m_TextureProperties[textureIdInt].m_Clip->h * m_TextureProperties[textureIdInt].m_Scale);
	}																						   

	
	SDL_RenderCopyEx(
		Renderer::GetRenderer(), m_Texture[textureIdInt],
		m_TextureProperties[textureIdInt].m_Clip,
		&renderQuad,		
		m_TextureProperties[textureIdInt].m_RotationDegrees,
		m_TextureProperties[textureIdInt].m_RotationCenter,
		m_TextureProperties[textureIdInt].m_FlipType);
		
}

void TextureHandler::transform(TextureList textureId, float scale, SDL_RendererFlip flipType, double angle, SDL_Point* center)
{
	setScale(textureId, scale);
	setRotate(textureId, angle, center);
	setFlip(textureId, flipType);
}

void TextureHandler::setPos(TextureList textureId, SDL_Point currentPos, SDL_Point change)
{
	m_TextureProperties[static_cast<int>(textureId)].m_Rect.x = (currentPos.x + change.x);
	m_TextureProperties[static_cast<int>(textureId)].m_Rect.y = (currentPos.y + change.y);
}

void TextureHandler::setScale(TextureList textureId, float ratio)
{
	m_TextureProperties[static_cast<int>(textureId)].m_Scale = ratio;
}

void TextureHandler::setColor(TextureList textureId, SDL_Color color) const
{
	SDL_SetTextureColorMod(m_Texture[static_cast<int>(textureId)], color.r, color.g, color.b);
}

void TextureHandler::setAlpha(TextureList textureId, Uint8 alpha) const
{
	SDL_SetTextureAlphaMod(m_Texture[static_cast<int>(textureId)], alpha);
}

void TextureHandler::setBlendMode(TextureList textureId, SDL_BlendMode blendMode) const
{	
	SDL_SetTextureBlendMode(m_Texture[static_cast<int>(textureId)], blendMode);
}

void TextureHandler::setRotate(TextureList textureId, double angle, SDL_Point* center)
{
	m_TextureProperties[static_cast<int>(textureId)].m_RotationDegrees = angle;
	m_TextureProperties[static_cast<int>(textureId)].m_RotationCenter = center;
}

void TextureHandler::setFlip(TextureList textureId, SDL_RendererFlip flipType)
{
	m_TextureProperties[static_cast<int>(textureId)].m_FlipType = flipType;
}

void TextureHandler::setClip(TextureList textureId, SDL_Rect* clip)
{
	m_TextureProperties[static_cast<int>(textureId)].m_Clip = clip;
}