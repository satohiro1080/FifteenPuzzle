#include "MouseInputManager.h"
#include <DxLib.h>

namespace
{
	static const int CURSOR_RADIUS = 16;
	static const int CURSOR_COLOR_NORMAL = 0xFFAAAA;
	static const int CURSOR_COLOR_CLICK = 0xFF0000;
	static const int CURSOR_ALPHA = 100;
}

MouseInputManager::MouseInputManager()
{
	m_cursorPosition = VECTOR2(0, 0);
	m_isClick = false;
}

MouseInputManager::~MouseInputManager()
{

}

void MouseInputManager::Update()
{
	int x, y;
	GetMousePoint(&x, &y);

	m_cursorPosition = VECTOR2((float)x, (float)y);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		m_isClick = true;
	}
	else
	{
		m_isClick = false;
	}
}

void MouseInputManager::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, CURSOR_ALPHA);
	{
		int x = (int)m_cursorPosition.x;
		int y = (int)m_cursorPosition.y;
		int color = m_isClick ?
			CURSOR_COLOR_CLICK :
			CURSOR_COLOR_NORMAL;
		DrawCircle(x, y, CURSOR_RADIUS, color);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool MouseInputManager::IsClickArea(const VECTOR2& areaPos, const VECTOR2& areaSize)
{
	return false;
}
