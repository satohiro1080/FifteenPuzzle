#include "SelectRect.h"

SelectRect::SelectRect()
{
	start = Vector2(0.0f, 0.0f);
	end = Vector2(0.0f, 0.0f);
}

SelectRect::~SelectRect()
{
}

void SelectRect::Update()
{
	State lastState = state;
	SelectBase::Update();
	if (state == SELECTING) 
	{
		if (lastState != state) 
		{
			start = mousePoint;
			end = start;
		}
		end = mousePoint;
	}
}

void SelectRect::Draw()
{
	if (state != SELECTING)
	{
		return;
	}
	DrawBox((int)start.x, (int)start.y, (int)end.x, (int)end.y, GetColor(255, 255, 255), FALSE);
}

bool SelectRect::CollisionDot(const Vector2& dotPos) const
{
	float left		= start.x < end.x ? start.x : end.x;
	float right		= start.x > end.x ? start.x : end.x;
	float top		= start.y < end.y ? start.y : end.y;
	float bottom	= start.y > end.y ? start.y : end.y;

	return (dotPos.x >= left && dotPos.x <= right && dotPos.y >= top && dotPos.y <= bottom);
}
