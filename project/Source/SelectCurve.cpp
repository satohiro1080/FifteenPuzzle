#include "SelectCurve.h"

namespace
{
	static const float POINT_INTERVAL = 20.0f;
}

SelectCurve::SelectCurve()
{
}

SelectCurve::~SelectCurve()
{
}

void SelectCurve::Update()
{
	State lastState = state;
	SelectBase::Update();
	if (lastState != state)
	{
		if (state == SELECTING)
		{
			points.clear();
			points.push_back(mousePoint);
		}
		else if (state == END)
		{
			points.push_back(mousePoint);
			points.push_back(points.front());
		}
	}
	else if (state == SELECTING)
	{
		pointUpdate();
	}
}

void SelectCurve::Draw()
{
	if (points.size() < 2)
	{
		return;
	}
	auto it = points.begin();
	Vector2 prev = *it;
	++it;
	for (; it != points.end(); ++it)
	{
		Vector2 curr = *it;
		DrawLine((int)prev.x, (int)prev.y, (int)curr.x, (int)curr.y, GetColor(255, 255, 255));
		prev = curr;
	}

	DrawLine((int)prev.x, (int)prev.y, (int)points.front().x, (int)points.front().y, GetColor(100, 100, 100));
}

bool SelectCurve::CollisionDot(const Vector2& dotPos) const
{
	if (state != END) return false;

	auto it = points.begin();
	Vector2 prev = *it;
	++it;

	int hitCount = 0;
	for (; it != points.end(); prev = *it++)
	{
		Vector2 curr = *it;

		if (prev.x < dotPos.x && curr.x < dotPos.x) continue;
			
		if ((prev.y <= dotPos.y && dotPos.y < curr.y) ||
			(curr.y <= dotPos.y && dotPos.y < prev.y))
		{
			Vector2 lineDir = (curr - prev).Norm();
			Vector2 downVec = Vector2(0, dotPos.y - curr.y);
			Vector2 horizontalVec = curr + (lineDir * V2::Dot(lineDir, downVec));

			if (horizontalVec.x < dotPos.x) continue;

			hitCount++;
		}

	}

	return (hitCount % 2) == 1;
}

void SelectCurve::pointUpdate()
{
	if ((points.back() - mousePoint).SquareSize() >= POINT_INTERVAL * POINT_INTERVAL)
	{
		points.push_back(mousePoint);

		if (points.size() > 1000)
		{
			points.pop_front();
		}
	}
}
