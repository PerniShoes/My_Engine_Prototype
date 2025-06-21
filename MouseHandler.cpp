#include "MouseHandler.h"

MouseHandler::MouseHandler()
	:m_PosX{ 0 }, m_PosY{ 0 }, m_Last_Left{ Last_Released }, m_Last_Right{ Last_Released }, m_Last_Middle{ Last_Released },
	m_LastTick{ 0 }, m_HoldDelay{ 0.15f }
{
	


}

MouseHandler::~MouseHandler()
{


}

void MouseHandler::updateState()
{
	updateMousePos();
	updateHoldTimers();
}

void MouseHandler::updateMousePos()
{
	SDL_GetMouseState(&m_PosX, &m_PosY);
}
void MouseHandler::updateHoldTimers()
{
	float elapsedTime{ 0.0f };

	elapsedTime = ((m_Time.getTimePassedInMs() - m_LastTick) / 1000.0f);
	m_LastTick = (float)m_Time.getTimePassedInMs();


	if (m_Last_Left == Last_Pressed || m_Last_Left == Last_Held)
	{
		HoldTimer.Left += elapsedTime;
	}
	else
	{
		HoldTimer.Left = 0.0f;
	}



	if (HoldTimer.Left >= m_HoldDelay)
	{
		m_Last_Left = Last_Held;
	}

	if (m_Last_Right == Last_Pressed || m_Last_Right == Last_Held)
	{
		HoldTimer.Right += elapsedTime;
	}
	else
	{
		HoldTimer.Right = 0.0f;
	}

	if (HoldTimer.Right >= m_HoldDelay)
	{
		m_Last_Right = Last_Held;
	}



	if (m_Last_Middle == Last_Pressed || m_Last_Middle == Last_Held)
	{
		HoldTimer.Middle += elapsedTime;
	}
	else
	{
		HoldTimer.Middle = 0.0f;
	}

	if (HoldTimer.Middle >= m_HoldDelay)
	{
		m_Last_Middle = Last_Held;
	}



}

bool MouseHandler::isMouseInside(SDL_Rect targetRect) const
{
	bool mouseInside = true;

	if (m_PosX < targetRect.x)
	{
		mouseInside = false;
	}
	else if (m_PosX > targetRect.x + targetRect.w)
	{
		mouseInside = false;
	}
	else if (m_PosY < targetRect.y)
	{
		mouseInside = false;
	}
	else if (m_PosY > targetRect.y + targetRect.h)
	{
		mouseInside = false;
	}

	return mouseInside;
}

void MouseHandler::handleEvents(SDL_Event& e)
{
	leftButton(e);
	rightButton(e);
	middleButton(e);
}

MouseState MouseHandler::getLBState()
{
	switch (m_Last_Left)
	{
	case Last_Released: return Released; break;
	case Last_Pressed: return Pressed; break;
	case Last_Held: return Held; break;
	default: return Released;
	}
}
MouseState MouseHandler::getRBState()
{
	switch (m_Last_Right)
	{
	case Last_Released: return Released; break;
	case Last_Pressed: return Pressed; break;
	case Last_Held: return Held; break;
	default: return Released;
	}
}
MouseState MouseHandler::getMBState()
{
	switch (m_Last_Middle)
	{
	case Last_Released: return Released; break;
	case Last_Pressed: return Pressed; break;
	case Last_Held: return Held; break;
	default: return Released;
	}
}

void MouseHandler::leftButton(SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			m_Last_Left = Last_Released;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			m_Last_Left = Last_Pressed; 
		}
	}
}
void MouseHandler::rightButton(SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_RIGHT)
	{
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			m_Last_Right = Last_Released;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			m_Last_Right = Last_Pressed;
		}
	}

}
void MouseHandler::middleButton(SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_MIDDLE)
	{
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			m_Last_Middle = Last_Released;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			m_Last_Middle = Last_Pressed;
		}
	}

}


