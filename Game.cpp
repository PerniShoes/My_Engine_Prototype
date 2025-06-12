#include "Game.h"

Game::Game()			
{
	//Debug::Print("Game constructor called\n");
	ObjectInit();
	
};

Game::~Game()
{

};

void Game::ObjectInit()
{


	m_WalkingSpriteClips[0].x = 0;
	m_WalkingSpriteClips[0].y = 0;
	m_WalkingSpriteClips[0].w = 64;
	m_WalkingSpriteClips[0].h = 205;

	m_WalkingSpriteClips[1].x = 64;
	m_WalkingSpriteClips[1].y = 0;
	m_WalkingSpriteClips[1].w = 64;
	m_WalkingSpriteClips[1].h = 205;

	m_WalkingSpriteClips[2].x = 128;
	m_WalkingSpriteClips[2].y = 0;
	m_WalkingSpriteClips[2].w = 64;
	m_WalkingSpriteClips[2].h = 205;

	m_WalkingSpriteClips[3].x = 192;
	m_WalkingSpriteClips[3].y = 0;
	m_WalkingSpriteClips[3].w = 64;
	m_WalkingSpriteClips[3].h = 205;

	m_BackgroundCheck = MOUSE_OUT;


	m_MousePosX = 0;
	m_MousePosY = 0;

	m_Value = 10;


	m_MouseInside = false;

	m_Quit = false;
	m_E = { 0 };

	m_BackgroundTextureProp.color = SDL_Color{ 255,255,255 };
	m_BackgroundTextureProp.pos = SDL_Point{ 0,0 };



	m_TestTextTextureProp.scale = 1.5f;
	m_TestTextTextureProp.pos = SDL_Point{ 100,400 };

	m_FooAnimatedTextureProp.frameSlow = 8;
	m_FooAnimatedTextureProp.currentClip = &m_WalkingSpriteClips[m_FooAnimatedTextureProp.currentFrame / m_FooAnimatedTextureProp.frameSlow];
	m_FooAnimatedTextureProp.pos = SDL_Point{ 200,100 };
	m_FooAnimatedTextureProp.scale = 1.0f;
	m_FooAnimatedTextureProp.rotationCenter = NULL;
	m_FooAnimatedTextureProp.currentFrame = 0;


};

bool Game::SDLInit()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		Debug::Print("SDL could not initialize! SDL Error: %s", SDL_GetError(),"\n");
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			Debug::Print("Warning: Linear texture filtering not enabled!");
		}

		if (Window::GetWindow() == NULL)
		{
			Debug::Print("Window could not be created! SDL Error: %s", SDL_GetError(),"\n");
			success = false;
		}

		else
		{
			if (Renderer::GetRenderer() == NULL)
			{
				Debug::Print("Renderer could not be created! SDL Error: %s", SDL_GetError(),"\n");
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(Renderer::GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					Debug::Print("SDL_image could not initialize! SDL_image Error: %s", IMG_GetError(),"\n");
					success = false;
				}
			}
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				Debug::Print("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError(),"\n");	
				success = false;
			}
			if (TTF_Init() == -1)
			{
				Debug::Print("SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError(),"\n");
				success = false;
			}
		}
	}



	return success;
};

bool Game::LoadMedia()
{
	bool success = true;
	
	m_Audio.LoadAudio();
	//m_Textures.loadTextures();

	m_TestTextTexture.setFont(TTF_OpenFont("Fonts/lazy.ttf", 28));
	if (m_TestTextTexture.getFont() == NULL)
	{
		Debug::Print("Failed to load lazy font! SDL_ttf Error: %s", TTF_GetError(),"\n");
		success = false;
	}
	else
	{

		if (!m_TestTextTexture.loadFromRenderedText("THIS IS MADNESSSSSSSSS"))
		{
			Debug::Print("Failed to render text texture!\n");
			success = false;
		}
	}


	if (!m_FooAnimatedTexture.loadFromFile("Images/foo_animated.png", 1))
	{
		success = false;
	}
	else
	{
		m_FooAnimatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if (!m_BackgroundTexture.loadFromFile("Images/Background.png"))	
	{
		success = false;
	}

	return success;
};

void Game::GameLoop()
{

	while (!m_Quit)
	{
		while (SDL_PollEvent(&m_E) != 0)
		{
			if (m_E.type == SDL_QUIT)
			{
				m_Quit = true;
			}
			else {

				Events();


			}
	
		}
		Logic();
		Rendering();
	}


};


void Game::Events()
{
	HandleMouseEvents();
	HandleKeyEvents();


};

void Game::HandleKeyEvents()
{
	if (m_E.type == SDL_KEYDOWN)
	{
		switch (m_E.key.keysym.sym)
		{
		case SDLK_1:	
			m_Audio.PlaySound(Audio::Low);			
			break;
		case SDLK_2:
			m_Audio.PlaySound(Audio::High);	
			break;
		case SDLK_3:
			m_Audio.PlaySound(Audio::Medium);		
			break;
		case SDLK_4:
			m_Audio.PlaySound(Audio::Scratch);		
			break;
		case SDLK_p:	
			m_Audio.PlayMusic(Audio::PauseOrResume); 
			break;
		case SDLK_m:		
			m_Audio.PlayMusic(Audio::DefaultMusic);
			break;
		case SDLK_o:	
			m_Audio.PlayMusic(Audio::Stop);	
			break;
		case SDLK_u:
			m_Audio.PlayMusic(Audio::HolyF);	
			break;
		case SDLK_i:
			m_Audio.PlayMusic(Audio::GimmeLove);	
			break;	
		case SDLK_y:
			m_Audio.PlayMusic(Audio::Pandemonium);	
			break;
		case SDLK_t:
			m_Audio.PlayMusic(Audio::AreYouGonnaBeMyGirl);
			break;
		case SDLK_l:
			m_Audio.PlayMusic(Audio::WezPigulke);
			break;
		case SDLK_k:
			m_Audio.PlayMusic(Audio::Hold);
			break;
		case SDLK_j:
			m_Audio.PlayMusic(Audio::Gold);
			break;
		case SDLK_h:
			m_Audio.PlayMusic(Audio::ThatsWhatILike);
			break;
		case SDLK_g:
			m_Audio.PlayMusic(Audio::ImComing);
			break;
		case SDLK_r:
			m_Audio.PlayMusic(Audio::BeautifulMadness);
			break;
		case SDLK_f:
			m_Audio.PlayMusic(Audio::ALittleMessedUp);
			break;
		case SDLK_q:
			m_FooAnimatedTextureProp.rotationDegrees += m_Value;
			break;
		case SDLK_a:
			m_FooAnimatedTextureProp.rotationDegrees -= m_Value;
			break;
		case SDLK_s:
			m_BackgroundTextureProp.color.r += m_Value;
			break;
		case SDLK_w:
			m_BackgroundTextureProp.color.g -= m_Value;
			break;
		case SDLK_e:
			m_BackgroundTextureProp.color.b -= m_Value;
			break;
		case SDLK_UP:
			m_FooAnimatedTextureProp.alpha += m_Value;
			break;
		case SDLK_DOWN:
			m_FooAnimatedTextureProp.alpha -= m_Value;
			break;
		case SDLK_LEFT:
			m_FooAnimatedTextureProp.flipType = SDL_FLIP_HORIZONTAL;
			break;
		case SDLK_RIGHT:
			m_FooAnimatedTextureProp.flipType = SDL_FLIP_NONE;
			break;
		case SDLK_0:
			m_FooAnimatedTextureProp.flipType = SDL_FLIP_VERTICAL;
			break;


		}
	}

};

void Game::HandleMouseEvents()
{
	if (m_E.type == SDL_MOUSEMOTION || m_E.type == SDL_MOUSEBUTTONDOWN || m_E.type == SDL_MOUSEBUTTONUP)
	{

		SDL_GetMouseState(&m_MousePosX, &m_MousePosY);
		m_MouseInside = true;

		if (m_MousePosX < 0)
		{
			m_MouseInside = false;
		}
		else if (m_MousePosY < 0)
		{
			m_MouseInside = false;
		}
		else if (m_MousePosY > 0 + m_BackgroundTexture.getHeight())
		{
			m_MouseInside = false;
		}
		else if (m_MousePosX > 0 + m_BackgroundTexture.getWidth())
		{
			m_MouseInside = false;
		}

		if (!m_MouseInside)
		{
			m_BackgroundCheck = MOUSE_OUT;
		}
		else
		{
			switch (m_E.type)
			{
			case SDL_MOUSEMOTION:
				m_BackgroundCheck = MOUSE_OVER_MOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_BackgroundCheck = MOUSE_DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				m_BackgroundCheck = MOUSE_UP;
				break;

			}

		}
	}
	if (m_MouseInside == true)
	{
		m_BackgroundTexture.setColor((m_BackgroundTextureProp.color));
	}
	else
	{
		SDL_Color darker = SDL_Color{ 125,125,125 };	
		m_BackgroundTexture.setColor(darker);	
	}

};


void Game::Logic()
{
	
	switch (m_BackgroundCheck)
	{
	case MOUSE_DOWN:
		Debug::Print("Mouse clicked on m_BackgroundTexture!\n");
		m_BackgroundCheck = MOUSE_OUT;
		break;
	case MOUSE_UP:
		Debug::Print("Mouse released on m_BackgroundTexture!\n");
		m_BackgroundCheck = MOUSE_OUT;
		break;
	case MOUSE_OVER_MOTION:
		Debug::Print("Mouse is hovering over m_BackgroundTexture!\n");
		m_BackgroundCheck = MOUSE_OUT;
		break;
	default:
		m_BackgroundCheck = MOUSE_OUT;
		break;
	}
	/*

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		Debug::Print("Up got pressed\n");
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		Debug::Print("Down got pressed\n");
	}
	*/

};


void Game::Rendering()
{

	SDL_Color white{ 0xFF, 0xFF, 0xFF, 0xFF }; // Later have it separate so you don't need to change "white" bellow 4x times to change the color
	
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_RenderClear(Renderer::GetRenderer());
	
	m_Textures.render(TextureHandler::Foo);
	
	
	
	RenderFromStruct(m_BackgroundTexture, m_BackgroundTextureProp);	
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);


	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);


	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_RenderSetViewport(Renderer::GetRenderer(), NULL);

	//m_FooAnimatedTexture.render(m_TestTextTextureProp.pos);
	//RenderFromStruct(m_TestTextTexture, m_TestTextTextureProp);
	//RenderFromStruct(m_FooAnimatedTexture, m_FooAnimatedTextureProp);

	SDL_RenderPresent(Renderer::GetRenderer());

};

void Game::ModifyTexture(SDL_My_Texture& texture, float scale, SDL_RendererFlip flipType, double angle, SDL_Point* center )
{
	texture.scale(scale);	
	texture.flip(flipType);	
	texture.rotate(angle, center);	

};

void Game::RenderFromStruct(SDL_My_Texture& texture, m_Texture& textureStruct)
{
	// Scale flip or rotate don't happen every frame. Probablly should make them more like:
	// X happens, THEN scale, NOT: scale everyframe and just change scale sometimes
	// So ModyfiTexture is good, but shouldn't be called everyframe (UNLESS needed)
	 
	// Should be done with logic checks, e.g: Mario picks up Red mushroom
	// In Events: PickedUpRedMushroom = true; 
	// Later in Logic: if(PickedUpRedMushroom){DestroyRedMushroom(); m_Textures.setScale(Mario, 2.0f); Set up power up timer}

	ModifyTexture(texture,
		textureStruct.scale,
		textureStruct.flipType,
		textureStruct.rotationDegrees, textureStruct.rotationCenter);

	texture.render(textureStruct.pos, textureStruct.currentClip);

};


void Game::Close()
{
	
	m_TestTextTexture.~SDL_My_Texture();	
	m_FooAnimatedTexture.~SDL_My_Texture();	
	m_BackgroundTexture.~SDL_My_Texture();	

	m_Audio.~Audio();
	TTF_Quit();	
	IMG_Quit();	
	SDL_Quit();
};





/*void Game::Rendering()
{

	SDL_Color white{ 0xFF, 0xFF, 0xFF, 0xFF }; // Later have it separate so you don't need to change "white" bellow 4x times to change the color
	//for (int i{}; i < 1000000; i++)
	//{
		SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
		SDL_RenderClear(Renderer::GetRenderer());
	//}

		//m_Textures.render(TextureHandler::Foo);

		//RenderFromStruct(m_BackgroundTexture, m_BackgroundTextureProp);

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, white.a);
	SDL_RenderSetViewport(Renderer::GetRenderer(), NULL);

	//RenderFromStruct(m_TestTextTexture, m_TestTextTextureProp);
	//RenderFromStruct(m_FooAnimatedTexture, m_FooAnimatedTextureProp);

	// animation:
	m_FooAnimatedTextureProp.currentClip = &m_WalkingSpriteClips[m_FooAnimatedTextureProp.currentFrame / m_FooAnimatedTextureProp.frameSlow];

	
	SDL_RenderPresent(Renderer::GetRenderer());

	// animation:

	++m_FooAnimatedTextureProp.currentFrame;

	if (m_FooAnimatedTextureProp.currentFrame / m_FooAnimatedTextureProp.frameSlow >= M_WALKING_ANIMATION_FRAMES)
	{
		m_FooAnimatedTextureProp.currentFrame = 0;
	}

};*/