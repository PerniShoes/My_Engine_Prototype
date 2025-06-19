#pragma once
#include <SDL.h>


#include "Window.h"
#include "Debug.h"
#include <string>
#include <sstream>




class Player
{
public:
    Player(int height, int width, int velocity);
    ~Player();


    void handleEvent(SDL_Event& e);
    void move();
    void setSize(int height, int width);

    SDL_Point getPosition() const;
    void setVelocity(int velocity);

private:


    SDL_Point m_Position;
    int m_Velocity;
    int m_Height;
    int m_Width;

    int m_VelocityY;
    int m_VelocityX;



};

