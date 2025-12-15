#include "MouseInputManager.h"
#include "../Library/Time.h"
#include <DxLib.h>

namespace
{
	static const int CURSOR_RADIUS = 16;
	static const int CURSOR_COLOR_NORMAL = 0xFFAAAA;
	static const int CURSOR_COLOR_CLICK = 0xFF0000;
	static const int CURSOR_ALPHA = 100;

	static const int AREA_ALPHA = 100;
	static const int AREA_COLOR_MOUSE_OVER = 0xAAFFAA;
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
	drawCursor();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, AREA_ALPHA);
	{
		for (const Area& area : m_currentFrameArea)
		{
			if (area.state < AreaState::MOUSE_OVER) continue;

			int x1 = (int)area.pos.x;
			int y1 = (int)area.pos.y;
			int x2 = (int)(area.pos.x + area.size.x);
			int y2 = (int)(area.pos.y + area.size.y);
			int color = AREA_COLOR_MOUSE_OVER;

			DrawBox(x1, y1, x2, y2, color, true);
		}
		m_currentFrameArea.clear();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MouseInputManager::drawCursor()
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
	if (IsMouseOverArea(areaPos, areaSize))
	{
		if (m_isClick) return true;
	}

	return false;
}

bool MouseInputManager::IsMouseOverArea(const VECTOR2& areaPos, const VECTOR2& areaSize)
{
	Area area = Area{ areaPos, areaSize, AreaState::NONE };

	VECTOR2 areaEnd = areaPos + areaSize;

	// 矩形内にカーソルがあればtrue
	bool ret = false;
	if (m_cursorPosition.x > areaPos.x &&
		m_cursorPosition.x <= areaEnd.x &&
		m_cursorPosition.y > areaPos.y &&
		m_cursorPosition.y <= areaEnd.y)
	{
		area.state = AreaState::MOUSE_OVER;
		ret = true;
	}

	m_currentFrameArea.push_back(area);

	return ret;
}
