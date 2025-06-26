#include "Game.h"

Game::Game()
	: m_Quit{ false }, m_E{ 0 }, m_BackgroundCheck{ MOUSE_OUT },
	m_Speed{ 0 }, m_PosChangeTemp{ 0 }, m_Ball{ SDL_Point{900,300+ m_BorderGirth}, 20, 20, 700.0f },
	m_BorderGirth{ 20 }, m_Player{ 0 + 40 - 10,
	0 + m_BorderGirth,
	5 }, m_TempMult{ 0.0f }, m_EnemyAi{ int(Window::GetWindowSize().x - 50.0f), 0 + m_BorderGirth }, m_MusicPlaying{ StopMusic }
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
	m_Player.handleEvent(m_E);

	HandleMouseEvents();
	HandleKeyEvents();

};

void Game::handleMusic()
{
	if (m_MusicPlaying == StopMusic)
	{
		if (m_Gamemode == EndlessMadness)
		{
			m_Audio.PlayMusic(EisenfunkPong);
		}
		else if (m_Gamemode == Survival)
		{
			m_Audio.PlayMusic(HeliosLexica);
		}
		else
		{
			m_Audio.PlayMusic(PressPlayMusic);
		}
	}

}

void Game::HandleKeyEvents()
{
	m_Player.handleEvent(m_E);
	
	m_Speed = 1;
	if (m_E.type == SDL_KEYDOWN)
	{
		switch (m_E.key.keysym.sym)
		{
		case SDLK_1:	
			m_Audio.PlaySound(PaddleSoundEffect);
			break;
		case SDLK_2:
			m_Audio.PlaySound(Score_sound);
			break;
		case SDLK_3:
			m_Audio.PlaySound(WallHitSoundEffect);
			break;
		case SDLK_4:
			
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
			m_TempMult = 1.0f;
			//m_BackgroundTextureProp.color.g -= m_Value;
			break;
		case SDLK_e:
			m_TempMult = 0.0f;
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
	if (m_Gamemode == Survival)
	{
		// No point scores
		// No ai
		

		// Stop ball until button is pressed to continue 
		// Show final score, ball mult setting board shrinking settings also transparent yes or no
		// and reset time
		
		// 
		// Turn on wall on right


	}


	if (m_Gamemode == EndlessMadness)
	{
		// Yes point scores
		
		// m_ScoreToWin = some insane number
		// Ai == unbeatable
		// Player size and velocity fluctuating
		// Board shrinking and ball mult overwritten
		// Music change to PLAY PONG



	}

	if (m_Gamemode == Vs_Ai)
	{
		// Most basic mode
		// No changes to score ball mult or board shrinking
		// Stop game if score reached
		// Ai difficulty increasing OR staying the same


	}


	m_Mouse.updateState();

	handleMusic();

	ballScoreHandling();

	//std::cout << (int)m_Ball.handleSoundEvents() << std::endl;
	switch ((int)m_Ball.handleSoundEvents())
	{
	case (int)PaddleHit: m_Audio.PlaySound(PaddleSoundEffect); break;
	case (int)WallHit: m_Audio.PlaySound(WallHitSoundEffect); break;
	default: break;
	}
	


	
	m_BoardBorderBottom = { 0,Window::GetWindowSize().y - m_BorderGirth,Window::GetWindowSize().x,Window::GetWindowSize().y };
	m_BoardBorderTop = { 0,0,Window::GetWindowSize().x,m_BorderGirth };
	m_BoardBorderRightTest = {Window::GetWindowSize().x - m_BorderGirth,0, Window::GetWindowSize().x,Window::GetWindowSize().y};

	m_Textures.setScale(PongPlayer, 1.0f);
	m_Player.setVelocity(500.0f);
	m_Player.setSize(m_Textures.getRect(PongPlayer)->h, m_Textures.getRect(PongPlayer)->w);

	m_Player.move(m_BorderGirth, true, m_Ball.getPosition(), m_Ball.getVelocity());
	m_Textures.setPos(PongPlayer, m_Player.getPosition());


	m_EnemyAi.setSize(m_Textures.getRect(EnemyPong)->h, m_Textures.getRect(EnemyPong)->w);
	m_EnemyAi.move(m_BorderGirth, m_AiDifficulty, m_Ball.getPosition(),m_Ball.getVelocity());
	m_Textures.setPos(EnemyPong, m_EnemyAi.getPosition());
	




	m_Ball.setVelocityMult(m_BallSpeedIncrease);
	m_Ball.move(Sides::Top, Sides::Right);

	m_Ball.handleCollision(m_Textures.getRect(EnemyPong));
	//m_Ball.handleCollision(&m_BoardBorderRightTest);
	m_Ball.handleCollision(&m_BoardBorderBottom);
	m_Ball.handleCollision(&m_BoardBorderTop);


	m_Ball.handleCollision(m_Textures.getRect(PongPlayer));
	m_Ball.setSize(m_Textures.getRect(PongBall)->h, m_Textures.getRect(PongBall)->w);
	m_Ball.setCollisionLines();

	m_Textures.setPos(PongBall, m_Ball.getPosition());

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
	SDL_Color white{ 255, 255, 255, 255 }; // Later have it separate so you don't need to change "white" bellow 4x times to change the color

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), black.r, black.g, black.b, black.a);
	SDL_RenderClear(Renderer::GetRenderer());

	// Pack things into functions to clean this mess up:

	switch (m_Gamemode)
	{
	case EndlessMadness:m_Textures.render(BackGroundBlackHole, true); break;
	case Vs_Ai:			m_Textures.render(BackgroundDazzlingForest, true); break;
	case Survival:		m_Textures.render(BackGroundSpace, true); break;
	}
	


	SDL_Rect fullScreen{ 0,0, Window::GetWindowSize().x,Window::GetWindowSize().y };

	SDL_SetRenderDrawBlendMode(Renderer::GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), black.r, black.g, black.b, 180);
	SDL_RenderFillRect(Renderer::GetRenderer(), &fullScreen);

	// Board borders
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, 100);
	SDL_RenderFillRect(Renderer::GetRenderer(), &m_BoardBorderBottom);
	SDL_RenderFillRect(Renderer::GetRenderer(), &m_BoardBorderTop);
	//SDL_RenderFillRect(Renderer::GetRenderer(), &m_BoardBorderRightTest);

	// Middle line 
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), white.r, white.g, white.b, 100);
	int middleLineSquareSize{ 8 };
	SDL_Rect middleScreenLine{ int(Window::GetWindowSize().x / 2)-middleLineSquareSize/2,0, middleLineSquareSize,middleLineSquareSize };
	int indexMax{ (Window::GetWindowSize().y-m_BorderGirth*2) / (middleLineSquareSize*2) };
	for (int i{ 0 }; i < indexMax; i++)
	{
		middleScreenLine.y = middleLineSquareSize + m_BorderGirth + (((middleLineSquareSize *2) * i));
		SDL_RenderFillRect(Renderer::GetRenderer(), &middleScreenLine);
	}
	//


	// Foreground:


	//m_Ball.drawCollisionLines();
	m_Textures.render(PongBall);

	m_Textures.render(EnemyPong);

	switch (m_PlayerPlatformColor)
	{
	case Pwhite		:m_Textures.setColor(PongPlayer, SDL_Color{ 255,255,255 }); break;
	case Pred		:m_Textures.setColor(PongPlayer, SDL_Color{ 255,0,0 }); break;
	case Pblue		:m_Textures.setColor(PongPlayer, SDL_Color{ 0,0,255	}); break;
	case Pgreen		:m_Textures.setColor(PongPlayer, SDL_Color{ 0,255,0 }); break;
	case Pyellow	:m_Textures.setColor(PongPlayer, SDL_Color{ 255,255,0 }); break;
	case Ppink		:m_Textures.setColor(PongPlayer, SDL_Color{ 255,51,204	}); break;
	case Ppurple	:m_Textures.setColor(PongPlayer, SDL_Color{ 153,0,204 }); break;
	case PlightBlue	:m_Textures.setColor(PongPlayer, SDL_Color{ 153,204,255 }); break;
	case Porange	:m_Textures.setColor(PongPlayer, SDL_Color{ 255,153,51 }); break;
	case almostTransparent:m_Textures.setColor(PongPlayer, SDL_Color{ 255,255,255 });
		m_Textures.setAlpha(PongPlayer, 5);
		break;

	}
	
	m_Textures.render(PongPlayer);
	//Debug::Print("X: ", m_Player.getPosition().x, "\n", "Y: ",m_Player.getPosition().y, "\n");


	// 9 being nine zeros in 2 147 483 647 (max score)
	int spacing{ 0 };
	int placeHolderCalc{ 0 };
	placeHolderCalc = m_PlayerScore;

	// Int overflow protection xd...
	if (m_PlayerScore >= 2147483647)
	{
		m_PlayerScore = 0;
	}
	if (m_AiScore >= 2147483647)
	{
		m_AiScore = 0;
	}

	for (int i{ 0+1 }; i < 9+1; i++)
	{
		placeHolderCalc /= 10*i;
		if (placeHolderCalc >= 1)
		{
			spacing = 1*i;
		}
		else
		{
			break;
		}
	}

	m_Textures.setPos(ScoreText, {int(Window::GetWindowSize().x / 2 - 75.0f-35.0f-(70.0f*spacing)), int(Window::GetWindowSize().y * 0.05f) + m_BorderGirth});
	m_Textures.changeText(ScoreText, std::to_string(m_PlayerScore));
	m_Textures.render(ScoreText);


	m_Textures.setPos(ScoreText, { int(Window::GetWindowSize().x / 2 + 75.0f), int(Window::GetWindowSize().y * 0.05f)+ m_BorderGirth });
	m_Textures.changeText(ScoreText, std::to_string(m_AiScore));
	m_Textures.render(ScoreText);

	m_Textures.changeText(TimeText,  m_Time.getTimePassedFull()); 
	m_Textures.setPos(TimeText, SDL_Point{
		(Window::GetWindowSize().x-250 - m_BorderGirth),
		20 + m_BorderGirth });
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

void Game::ballScoreHandling()
{
	if (m_Ball.getPosition().x >= Window::GetWindowSize().x +50)
	{
		m_Ball.restartBall();
		m_PlayerScore += 1;
		m_Audio.PlaySound(Score_sound);
	}
	else if (m_Ball.getPosition().x < 0 - 50)
	{
		m_Ball.restartBall();
		m_AiScore += 1;
		m_Audio.PlaySound(Score_sound);
	}
	
}


