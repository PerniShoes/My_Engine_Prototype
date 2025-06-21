#include "Game.h"

Game::Game()
	: m_Quit{ false }, m_E{ 0 }, m_BackgroundCheck{ MOUSE_OUT },
	m_MousePosX{ 0 }, m_MousePosY{ 0 }, m_MouseInside{ false }, m_Speed{ 0 }, m_PosChangeTemp{ 0 }, m_Player{ 0,0,5 }
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
	m_Player.handleEvent(m_E);

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
			whichFrame = 0;
			//m_BackgroundTextureProp.color.g -= m_Value;
			break;
		case SDLK_e:
			whichFrame = 5;
			//m_BackgroundTextureProp.color.b -= m_Value;
			break;
		case SDLK_UP:
			whichFrame = 3;
			m_PosChangeTemp.y -= m_Speed;
			//m_FooAnimatedTextureProp.alpha += m_Value;
			break;
		case SDLK_DOWN:
			whichFrame = 2;
			m_PosChangeTemp.y += m_Speed;
			//m_FooAnimatedTextureProp.alpha -= m_Value;
			break;
		case SDLK_LEFT:
			whichFrame = 1;
			m_PosChangeTemp.x -= m_Speed;
			//m_FooAnimatedTextureProp.flipType = SDL_FLIP_HORIZONTAL;
			break;
		case SDLK_RIGHT:
			whichFrame = 4;
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
	m_Mouse.handleEvents(m_E);


};

void Game::Logic()
{
	m_Mouse.updateState();

	if (m_Mouse.getLBState() == Held)
	{
		// DO CRAZY SHIT
	}



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

	m_Player.setSize(m_Textures.getRect(PongPlayer).h, m_Textures.getRect(PongPlayer).w);
	m_Player.move();

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

	/*m_Textures.setScale(BackgroundAlien, 2.0f);
	m_Textures.setPos(BackgroundAlien, { 0, -150 });
	m_Textures.setCurrentClip(BackgroundAlien, whichFrame);
	m_Textures.render(BackgroundAlien);*/

	m_Textures.setScale(PongPlayer,1.0f);
	m_Textures.setPos(PongPlayer, m_Player.getPosition());
	m_Textures.render(PongPlayer);
	//Debug::Print("X: ", m_Player.getPosition().x, "\n", "Y: ",m_Player.getPosition().y, "\n");


	m_Textures.setPos(PongBall, { 200, 200 }); 
	m_Textures.render(PongBall);

	m_Textures.setPos(FireProjectiles, { 400,400 });
	m_Textures.setScale(FireProjectiles, 1.0f);
	m_Textures.setCurrentClip(FireProjectiles, 2);
	m_Textures.render(FireProjectiles);

	m_Textures.changeText(TimeText,  m_Time.getTimePassedFull()); 
	m_Textures.setPos(TimeText, SDL_Point{
		(Window::GetWindowSize().x/2-100),
		50});
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


