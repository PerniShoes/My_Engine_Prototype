#include "TextureHandler.h"

TextureHandler::TextureHandler()

{

};

TextureHandler::~TextureHandler()
{
	freeResources();
};

void TextureHandler::setAllPaths()
{
	// Obviously not good code, too much repetition, change later:

	// Images
	setPath(Background, "Images/background.png");
	setPath(Foo, "Images/foo_animated.png");
	setPath(FuckEverything, "Images/fuck_everything.png");
	setPath(Hero, "Images/Hero.bmp");

	setPath(PongPlayer, "Images/PongPlayer.png");
	setPath(PongBall, "Images/PongBall.png");

	// Sprite Sheets
	setPath(LumberJackMove, "Images/LumberJackMove.png");
	setClipProp(LumberJackMove, { 0,0, 140,140 });

	setPath(FireProjectiles, "Images/500_Bullets/BulletsDrugie.png");
	setClipProp(FireProjectiles, { 0,0,24,24 });

	setPath(BlueEffects, "Images/VFX/BlueBulletsMINE.png");
	setClipProp(BlueEffects, { 0,0,32,32 });

	setPath(Tiles, "Images/Tiles.png");
	setClipProp(Tiles, { 0, 0, 16, 48 });

	setPath(BackgroundAlien, "Images/BackgroundSprite.jpg");
	setClipProp(BackgroundAlien, { 0,0, 640, 640 });

	// Fonts
	setPath(MainText, "Fonts/lazy.ttf");
	initText(MainText, "THIS IS MADNESS");
	setFont(MainText);

	setPath(TimeText, "Fonts/Digital Dismay.ttf");
	initText(TimeText, "Place Holder", 48);
	setFont(TimeText);


}

void TextureHandler::setPath(TextureList textureId, const char* text)
{
	m_TextureProperties[static_cast<int>(textureId)].m_Path = static_cast<std::string>(text);
}

void TextureHandler::setClipProp(TextureList textureId, SDL_Rect clipProp)
{
	m_TextureProperties[static_cast<int>(textureId)].m_ClipProp = clipProp;
}

bool TextureHandler::loadTextures()
{
	bool success = true;

	setAllPaths();

	for (int index{ 0 }; index < static_cast<int>(TotalTextures); index++)
	{
		m_TextureProperties[index].m_Scale = 1.0f;
		success = createTextureFromSurface(static_cast<TextureList>(index));

		if (success == false)
		{
			return success;
		}
	}

	setClipList(BlueEffects, 16, 8, 4);
	setClipList(FireProjectiles, 15, 24, 8);
	setClipList(LumberJackMove, 4, 6, 6);
	setClipList(Tiles, 1, 24, 24);
	setClipList(BackgroundAlien, 2, 3, 1);

	return success;
};


bool TextureHandler::createTextureFromSurface(TextureList textureId)
{
	SDL_Surface* surface;
	bool success = true;
	int textureIdInt = static_cast<int>(textureId);

	if (m_TextureProperties[textureIdInt].m_IsText)
	{
		surface = TTF_RenderText_Solid(m_TextureProperties[textureIdInt].m_Font,
			m_TextureProperties[textureIdInt].m_Text.c_str(), m_TextureProperties[textureIdInt].m_Color);

		if (surface == NULL)
		{
			Debug::Print("Unable to render text surface! TextureId: ", textureIdInt, " SDL_ttf Error : %s ", TTF_GetError(), "\n");
			success = false;
			return success;
		}
	}
	else
	{
		surface = IMG_Load(m_TextureProperties[textureIdInt].m_Path.c_str());

		if (surface == NULL)
		{
			Debug::Print("Unable to load image from file %! TextureId: ", textureIdInt, " SDL_image Error : %s ", IMG_GetError(), "\n");
			success = false;
			return success;
		}

	}
	if (m_Texture[textureIdInt] != NULL)
	{
		SDL_DestroyTexture(m_Texture[textureIdInt]);
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
	for (int index{ 0 }; index < static_cast<int>(TotalTextures); index++)
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


void TextureHandler::initText(TextureList textureId, const char* text, int ptSize, SDL_Color color)
{
	int textureIdInt = static_cast<int>(textureId);
	m_TextureProperties[textureIdInt].m_IsText = true;
	m_TextureProperties[textureIdInt].m_Text = static_cast<std::string>(text);	
	m_TextureProperties[textureIdInt].m_PtSize = ptSize;
	m_TextureProperties[textureIdInt].m_Color = color;

};

void TextureHandler::setFont(TextureList textureId)
{
	m_TextureProperties[static_cast<int>(textureId)].m_Font = TTF_OpenFont(
		m_TextureProperties[static_cast<int>(textureId)].m_Path.c_str(),
		m_TextureProperties[static_cast<int>(textureId)].m_PtSize);
}

void TextureHandler::changeText(TextureList textureId, std::string text)
{
	m_TextureProperties[static_cast<int>(textureId)].m_Text = static_cast<std::string>(text);
	createTextureFromSurface(textureId);
}


void TextureHandler::render(TextureList textureId) const
{
	int textureIdInt = static_cast<int>(textureId);

	SDL_Rect renderQuad{ 
		m_TextureProperties[textureIdInt].m_Rect.x,
		m_TextureProperties[textureIdInt].m_Rect.y,
		int(m_TextureProperties[textureIdInt].m_Rect.w * m_TextureProperties[textureIdInt].m_Scale),
		int(m_TextureProperties[textureIdInt].m_Rect.h * m_TextureProperties[textureIdInt].m_Scale)};


	if (m_TextureProperties[textureIdInt].m_CurrentClip != NULL)
	{
		renderQuad.w = int(m_TextureProperties[textureIdInt].m_CurrentClip->w * m_TextureProperties[textureIdInt].m_Scale);
		renderQuad.h = int(m_TextureProperties[textureIdInt].m_CurrentClip->h * m_TextureProperties[textureIdInt].m_Scale);
	}																						   

	
	SDL_RenderCopyEx(
		Renderer::GetRenderer(), m_Texture[textureIdInt],
		m_TextureProperties[textureIdInt].m_CurrentClip,
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


void TextureHandler::setScaleAll(float ratio)
{
	for (int index{ 0 }; index < static_cast<int>(TotalTextures); index++)
	{
		m_TextureProperties[index].m_Scale = ratio;

	}
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


void TextureHandler::setCurrentClip(TextureList textureId, int frameNumber)
{
	m_TextureProperties[static_cast<int>(textureId)].m_CurrentClip = &m_TextureProperties[static_cast<int>(textureId)].m_ClipList[frameNumber];
}

void TextureHandler::setClipList(TextureList textureId, int rowAmount, int columnAmount, int framesPerAnimation)
{
SDL_Rect clipProp = m_TextureProperties[static_cast<int>(textureId)].m_ClipProp;

m_TextureProperties[static_cast<int>(textureId)].m_FramesPerAnim = framesPerAnimation;

	for (int columnIndex{ 0 }; columnIndex < rowAmount; columnIndex++)
	{
		for (int rowIndex{ 0 }; rowIndex < columnAmount; rowIndex++)
		{
			m_TextureProperties[static_cast<int>(textureId)].m_ClipList.push_back(
				SDL_Rect{ 
				clipProp.x + rowIndex *clipProp.w,
				clipProp.y + columnIndex *clipProp.h,
				clipProp.w,
				clipProp.h });
		}
	}
}

void TextureHandler::animate(TextureList textureId, int spriteNumber, float speed)
{
	int spriteWanted = spriteNumber;
	int textureIdInt = static_cast<int>(textureId);
	spriteWanted = (spriteNumber * m_TextureProperties[textureIdInt].m_FramesPerAnim);
	
	float elapsedTime{ 0.0f };

	elapsedTime = ((m_Time.getTimePassedInMs() - m_TextureProperties[textureIdInt].m_LastTick)/1000.0f);
	//std::cout << elapsedTime << std::endl;

	m_TextureProperties[textureIdInt].m_LastTick = static_cast<float>(m_Time.getTimePassedInMs());
	
	m_TextureProperties[textureIdInt].m_FrameCounter += (speed*elapsedTime);
	if (textureIdInt == 8)
	{
		std::cout << m_TextureProperties[textureIdInt].m_FramesPerAnim << std::endl;
	}
	if (m_TextureProperties[textureIdInt].m_FrameCounter >= m_TextureProperties[textureIdInt].m_FramesPerAnim)

	{
		m_TextureProperties[textureIdInt].m_FrameCounter = 0.0f;
	}
	setCurrentClip(textureId, int(spriteWanted + m_TextureProperties[textureIdInt].m_FrameCounter));
}


SDL_Rect TextureHandler::getRect(TextureList textureId)
{
	SDL_Rect tempRect{};
	m_TextureProperties[(int)textureId].m_Rect;
	tempRect.x = m_TextureProperties[(int)textureId].m_Rect.x;
	tempRect.y = m_TextureProperties[(int)textureId].m_Rect.y;
	tempRect.h = m_TextureProperties[(int)textureId].m_Rect.h * m_TextureProperties[(int)textureId].m_Scale;
	tempRect.w = m_TextureProperties[(int)textureId].m_Rect.w * m_TextureProperties[(int)textureId].m_Scale;

	return tempRect;
}
