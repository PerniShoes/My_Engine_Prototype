#pragma once // NOLINT
#include <SDL.h>
#include "Debug.h"

class Window
{
public:

	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	 
	static Window& Get()
	{
		//Debug::Print("Get function called\n");
		static Window s_Instance;
		return s_Instance;	
	}

	static SDL_Window* GetWindow() { return Get().GetWindowImpl();};

private:

	Window() 
	{
		Window_Instance = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s_SCREEN_WIDTH, s_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		//Debug::Print("Constructor called\n");
	};

	~Window()
	{
		SDL_DestroyWindow(Window_Instance);
		Window_Instance = NULL;
	}

	SDL_Window* GetWindowImpl() { return Window_Instance; };
	
	SDL_Window* Window_Instance;
	static const int s_SCREEN_WIDTH = 1000;
	static const int s_SCREEN_HEIGHT = 800;
};

