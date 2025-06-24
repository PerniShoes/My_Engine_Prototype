#pragma once
#include "SDL.h"
#include "Debug.h"
#include "TimeHandler.h"
#include "Window.h"
#include "Renderer.h"

enum class Sides
{
    NoCollision = -1,
    Left = 0,
    Right = 1,
    Bottom = 2,
    Top = 3,

    SidesTotal = 4
};

enum CollisionLinesId
{
    // Collision detection assumes:
    // -Even amount of lines per side
    // -Lines in enum being in order: Left, Right, Top, Bottom
    
    // Vertical
    LeftTop = 0,
    LeftBottom = 1,

    RightTop = 2,
    RightBottom = 3,

    // Horizontal
    TopLeft = 4,
    TopRight = 5,

    BottomLeft = 6,
    BottomRight = 7,

    TotalLines = 8

};


class Ball
{

public:
    Ball(SDL_Point startingPos = {0, 0}, int width = 20, int height = 20, float velocity = 5);
    ~Ball();


    void move(Sides startingCollisionVert = Sides::NoCollision, Sides startingCollisionHorizontal = Sides::NoCollision);

    void handleEvent(SDL_Event& e);

    void handleCollision(SDL_Rect* targetRect);
    
    void drawCollisionLines()const;

    void setSize(int height, int width);
    void setVelocity(float velocity);

    // Debug
    void setPos(SDL_Point pos); 


    SDL_Point getPosition() const;
    void setCollisionLines();

private:
    // Works with even amount of lines per side
    void detectCollision(SDL_Rect* targetRect);
   
    SDL_Rect m_BallRect;

    float m_Velocity;
    float m_VelocityY;
    float m_VelocityX;

    struct Line
    {
        SDL_Point lineStart;
        SDL_Point lineEnd;
    };

    // Lines go outwards from ball
    Line m_CollisionLines[TotalLines]{};
    bool m_CollisionDetected[TotalLines];

    Sides m_LastHitVert;
    Sides m_LastHitHorizontal;
};

