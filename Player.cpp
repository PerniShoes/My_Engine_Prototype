#include "Player.h"


Player::Player(int posX, int posY, float velocity)
    :m_Position{ posX,posY }, m_Height{ 10 }, m_Width{ 10 }, m_Velocity{ velocity }, m_VelocityY{ 0 }, m_VelocityX{ 0 }
{


}

Player::~Player()
{

}

SDL_Point Player::getPosition() const
{
    return m_Position;
}

void Player::move(int borderGirth)
{

    m_Position.x += (int)m_VelocityX;
    if (m_Position.x < 0 || (m_Position.x + m_Width) > Window::GetWindowSize().x)
    {
        m_Position.x -= (int)m_VelocityX;
    }

    m_Position.y += (int)m_VelocityY;
    if (m_Position.y < 0 + borderGirth || (m_Position.y + m_Height) > Window::GetWindowSize().y - borderGirth)
    {
        m_Position.y -= (int)m_VelocityY;
    }

}

void Player::setSize(int height, int width)
{
    m_Height = height;
    m_Width = width;
}

void Player::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: m_VelocityY -= m_Velocity; break;
        case SDLK_DOWN: m_VelocityY += m_Velocity; break;
        //case SDLK_LEFT: m_VelocityX -= m_Velocity; break;
        //case SDLK_RIGHT: m_VelocityX += m_Velocity; break;
        }
    }
    
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    { 
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: m_VelocityY += m_Velocity; break;
        case SDLK_DOWN: m_VelocityY -= m_Velocity; break;
        // case SDLK_LEFT: m_VelocityX += m_Velocity; break;
        //case SDLK_RIGHT: m_VelocityX -= m_Velocity; break;
        }

    }

}

void Player::setVelocity(float velocity)
{
    m_Velocity = velocity;
}