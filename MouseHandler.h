#pragma once
#include "SDL.h"
#include "Debug.h"
#include "TimeHandler.h"

enum class MouseState
{
    Pressed = 0,
    Released = 1,
    Held = 2,

    Total = 3
};
using enum MouseState;

class MouseHandler
{
public:
    MouseHandler();
    ~MouseHandler();

    bool isMouseInside(SDL_Rect targetRect) const;

    void handleEvents(SDL_Event& e);

    MouseState getLBState();
    MouseState getRBState();
    MouseState getMBState();
    SDL_Point getMousePos();

    void setMouseHoldDelay(float delay);


    // Needs to run everyframe
    void updateState();

private:

    void updateHoldTimers();
    void updateMousePos();
    void leftButton(SDL_Event& e);
    void rightButton(SDL_Event& e);
    void middleButton(SDL_Event& e);

    enum class Last_MouseState
    {
        Last_Pressed = 0,
        Last_Released = 1,
        Last_Held = 2,

        Last_Total = 3

    }m_Last_Left, m_Last_Right, m_Last_Middle;
    using enum Last_MouseState;

    int m_PosX;
    int m_PosY;

    struct Timer
    {
        float Left;
        float Right;
        float Middle;
    }HoldTimer{};

    float m_LastTick;
    float m_HoldDelay;

    TimeHandler m_Time;


};
