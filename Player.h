#pragma once
#include <SDL.h>


#include "Window.h"
#include "Debug.h"
#include <string>
#include <sstream>




class Player
{
public:
    Player(int posX = 0, int posY = 0, float velocity = 5.0f);
    ~Player();


    void handleEvent(SDL_Event& e);
    void move(int borderGirth);
    void setSize(int height, int width);

    SDL_Point getPosition() const;
    void setVelocity(float velocity);

private:

    SDL_Point m_Position;
    int m_Height;
    int m_Width;

    float m_Velocity;
    float m_VelocityY;
    float m_VelocityX;


};

