#include "SDL_My_Texture.h"

SDL_My_Texture::SDL_My_Texture()
{
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;

	m_ScaleRatio = 1.0f;

	m_Angle = 0.0;
	m_Center = NULL;
	m_Flip = SDL_FLIP_NONE;

	m_Font = NULL;

	
};

SDL_My_Texture::~SDL_My_Texture()
{
	freeResources();

};

void SDL_My_Texture::setFont(TTF_Font* font)
{
	m_Font = font;
}

TTF_Font* SDL_My_Texture::getFont()
{
	return m_Font;		
}

bool SDL_My_Texture::loadFromRenderedText(const std::string& textureText)
{
	freeResources();
	SDL_Color textColor{ 255, 255, 255 };

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, textureText.c_str(), textColor);



	if (textSurface == NULL)
	{

		Debug::Print("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}





	else
	{
		m_Texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), textSurface);
		if (m_Texture == NULL)
		{
			Debug::Print("Unable to create Texture from Surface SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			m_Width = textSurface->w;
			m_Height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);	
		
	}
	return m_Texture != NULL;

}

bool SDL_My_Texture::loadFromFile(const std::string& path, int colorKey)
{

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		Debug::Print("Unable to load image %! SDL_image Error: %s ", path.c_str(), " ",IMG_GetError(), "\n");
	}
	else
	{
		SDL_SetColorKey(loadedSurface, colorKey, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), loadedSurface);
		if (newTexture == NULL)
		{
			Debug::Print("Unable to create texture from %s! SDL Error: %s", path.c_str()," ", SDL_GetError(),"\n");
		}
		else
		{
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;
		}


		SDL_FreeSurface(loadedSurface);
	}

	m_Texture = newTexture;
	if (m_Texture == NULL)
	{
		Debug::Print("Failed to load: ", path, " image!\n");
	};
	return m_Texture != NULL;

};

void SDL_My_Texture::freeResources()
{
	if (m_Texture != NULL)
	{
		TTF_CloseFont(m_Font);
		m_Font = NULL;	

		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
		m_ScaleRatio = 1.0f;

		m_Angle = 0.0;
		m_Center = NULL;
		m_Flip = SDL_FLIP_NONE;

	}

};

void SDL_My_Texture::scale(float ratio)
{
	if (ratio > 0.0f)
	{
		m_ScaleRatio = ratio;
	}
}

void SDL_My_Texture::render(SDL_Point pos, SDL_Rect* clip)
{

	SDL_Rect renderQuad{ pos.x, pos.y, int(m_Width * m_ScaleRatio), int(m_Height * m_ScaleRatio) };

	if (clip != NULL)
	{
		renderQuad.w = int(clip->w * m_ScaleRatio);
		renderQuad.h = int(clip->h * m_ScaleRatio);
	}

	SDL_RenderCopyEx(Renderer::GetRenderer(), m_Texture, clip, &renderQuad, m_Angle, m_Center, m_Flip);
};

void SDL_My_Texture::setColor(SDL_Color color)
{
	SDL_SetTextureColorMod(m_Texture, color.r, color.g, color.b);

}

void SDL_My_Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void SDL_My_Texture::setBlendMode(SDL_BlendMode blendMode)
{

	SDL_SetTextureBlendMode(m_Texture, blendMode);
}

int SDL_My_Texture::getHeight()
{
	return m_Height;
};

int SDL_My_Texture::getWidth()
{
	return m_Width;
};

void SDL_My_Texture::flip(SDL_RendererFlip flip)
{

	m_Flip = flip;

}

void SDL_My_Texture::rotate(double angle, SDL_Point* center)
{
	m_Angle = angle;
	m_Center = center;
}