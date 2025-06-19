#include "Game.h"

Game::Game()
	: m_Quit{ false }, m_E{ 0 }, m_BackgroundCheck{ MOUSE_OUT },
	m_MousePosX{ 0 }, m_MousePosY{ 0 }, m_MouseInside{ false }, m_Speed{ 0 }, m_PosChangeTemp{ 0 }
{

	
};

Game::~Game()
{

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
	
	success = m_Audio.LoadAudio();
	if (!success)
	{
		Debug::Print("Audio failed to initialize!\n");
	}

	success = m_Textures.loadTextures();
	if (!success)
	{
		Debug::Print("Textures failed to initialize!\n");
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

	m_Speed = 1;
	if (m_E.type == SDL_KEYDOWN)
	{
		switch (m_E.key.keysym.sym)
		{
		case SDLK_1:	
			m_Audio.PlaySound(LowSound);
			break;
		case SDLK_2:
			m_Audio.PlaySound(HighSound);
			break;
		case SDLK_3:
			m_Audio.PlaySound(MediumSound);
			break;
		case SDLK_4:
			m_Audio.PlaySound(ScratchSound);
			break;
		case SDLK_p:	
			m_Audio.PlayMusic(PauseOrResume); 
			break;
		case SDLK_m:		
			m_Audio.PlayMusic(DefaultMusic);
			break;
		case SDLK_o:	
			m_Audio.PlayMusic(StopMusic);	
			break;
		case SDLK_u:
			m_Audio.PlayMusic(HolyF);	
			break;
		case SDLK_i:
			m_Audio.PlayMusic(GimmeLove);	
			break;	
		case SDLK_y:
			m_Audio.PlayMusic(Pandemonium);	
			break;
		case SDLK_t:
			m_Audio.PlayMusic(AreYouGonnaBeMyGirl);
			break;
		case SDLK_l:
			m_Audio.PlayMusic(WezPigulke);
			break;
		case SDLK_k:
			m_Audio.PlayMusic(Hold);
			break;
		case SDLK_j:
			m_Audio.PlayMusic(Gold);
			break;
		case SDLK_h:
			m_Audio.PlayMusic(ThatsWhatILike);
			break;
		case SDLK_g:
			m_Audio.PlayMusic(ImComing);
			break;
		case SDLK_r:
			m_Audio.PlayMusic(BeautifulMadness);
			break;
		case SDLK_f:
			m_Audio.PlayMusic(ALittleMessedUp);
			break;
		case SDLK_q:
			//m_FooAnimatedTextureProp.rotationDegrees += m_Value;
			break;
		case SDLK_a:
			//m_FooAnimatedTextureProp.rotationDegrees -= m_Value;
			break;
		case SDLK_s:
			//m_BackgroundTextureProp.color.r += m_Value;
			break;
		case SDLK_w:
			//m_BackgroundTextureProp.color.g -= m_Value;
			break;
		case SDLK_e:
			//m_BackgroundTextureProp.color.b -= m_Value;
			break;
		case SDLK_UP:
			m_PosChangeTemp.y -= m_Speed;
			//m_FooAnimatedTextureProp.alpha += m_Value;
			break;
		case SDLK_DOWN:
			m_PosChangeTemp.y += m_Speed;
			//m_FooAnimatedTextureProp.alpha -= m_Value;
			break;
		case SDLK_LEFT:
			m_PosChangeTemp.x -= m_Speed;
			//m_FooAnimatedTextureProp.flipType = SDL_FLIP_HORIZONTAL;
			break;
		case SDLK_RIGHT:
			m_PosChangeTemp.x += m_Speed;
			//m_FooAnimatedTextureProp.flipType = SDL_FLIP_NONE;
			break;
		case SDLK_0:
			//m_FooAnimatedTextureProp.flipType = SDL_FLIP_VERTICAL;
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

	//	if (m_MousePosX < 0)
	//	{
	//		m_MouseInside = false;
	//	}
	//	else if (m_MousePosY < 0)
	//	{
	//		m_MouseInside = false;
	//	}
	//	else if (m_MousePosY > 0 + m_BackgroundTexture.getHeight())
	//	{
	//		m_MouseInside = false;
	//	}
	//	else if (m_MousePosX > 0 + m_BackgroundTexture.getWidth())
	//	{
	//		m_MouseInside = false;
	//	}

	//	if (!m_MouseInside)
	//	{
	//		m_BackgroundCheck = MOUSE_OUT;
	//	}
	//	else
	//	{
	//		switch (m_E.type)
	//		{
	//		case SDL_MOUSEMOTION:
	//			m_BackgroundCheck = MOUSE_OVER_MOTION;
	//			break;
	//		case SDL_MOUSEBUTTONDOWN:
	//			m_BackgroundCheck = MOUSE_DOWN;
	//			break;
	//		case SDL_MOUSEBUTTONUP:
	//			m_BackgroundCheck = MOUSE_UP;
	//			break;

	//		}

	//	}
	//}
	//if (m_MouseInside == true)
	//{
	//	m_BackgroundTexture.setColor((m_BackgroundTextureProp.color));
	//}
	//else
	//{
	//	SDL_Color darker = SDL_Color{ 125,125,125 };	
	//	m_BackgroundTexture.setColor(darker);	
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
	SDL_Color black{ 0, 0, 0, 255 };
	//SDL_Color white{ 255, 255, 255, 255 }; // Later have it separate so you don't need to change "white" bellow 4x times to change the color

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), black.r, black.g, black.b, black.a);
	SDL_RenderClear(Renderer::GetRenderer());



	m_Textures.setPos(FuckEverything, SDL_Point{ 0,0 });
	m_Textures.setScale(FuckEverything, 0.3f);
	m_Textures.render(FuckEverything);

	m_Textures.setScaleAll(1.0f);


	float speed{ 12.0f + m_PosChangeTemp.x };

	m_Textures.setScale(BlueEffects, 3.0f);
	m_Textures.setPos(BlueEffects, SDL_Point{ 500, 130 });
	m_Textures.animate(BlueEffects, 30, speed);
	m_Textures.render(BlueEffects);


	m_Textures.setPos(LumberJackMove, SDL_Point{ 700, 100 });
	m_Textures.animate(LumberJackMove, 1, speed);
	m_Textures.render(LumberJackMove);



	m_Textures.changeText(TimeText,  m_Time.getTimePassedFull()); 
	m_Textures.setPos(TimeText, SDL_Point{250+ m_PosChangeTemp.x, 200+ m_PosChangeTemp.y });
	m_Textures.render(TimeText);




	SDL_SetRenderDrawColor(Renderer::GetRenderer(), black.r, black.g, black.b, black.a);
	SDL_RenderSetViewport(Renderer::GetRenderer(), NULL);

	SDL_RenderPresent(Renderer::GetRenderer());

};


void Game::Close()
{
	
	m_Textures.~TextureHandler();
	m_Audio.~Audio();
	TTF_Quit();	
	IMG_Quit();	
	SDL_Quit();
};


