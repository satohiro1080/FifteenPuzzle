#include "ColorDot.h"

namespace
{
	static const unsigned int COLORS[] = {
		GetColor(255, 0, 0),
		GetColor(0, 0, 255),
		GetColor(0, 255, 0),
	};
	static const int COLOR_COUNT = sizeof(COLORS) / sizeof(COLORS[0]);
	static const float RADIUS = 4.0f;
}

ColorDotBase::ColorDotBase()
{
	radius = RADIUS;
	SetColorIndex(0);
	isSelected = false;
}

ColorDotBase::~ColorDotBase()
{
}

void ColorDotBase::Update()
{
}

void ColorDotBase::Draw()
{
	Vector2 position = GetPosition();

	if (isSelected) {
		DrawCircle((int)position.x, (int)position.y, (int)(radius + 5.0f), GetColor(255, 255, 255), TRUE);
	}
	DrawCircle((int)position.x, (int)position.y, (int)radius, color, TRUE);
}

void ColorDotBase::SetColorIndex(int index)
{
	if (index < 0 || index >= COLOR_COUNT) {
		return;
	}

	colorIndex = index;
	color = COLORS[colorIndex];
}

void ColorDotBase::SetColorIndexToNext()
{
	int nextIndex = (colorIndex + 1) % COLOR_COUNT;
	SetColorIndex(nextIndex);
}

void ColorDot3D::Draw()
{
	if (isSelected) {
		SetWriteZBuffer3D(FALSE);
		SetUseLighting(FALSE);
		DrawSphere3D(position, radius + 1.0f, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
		SetWriteZBuffer3D(TRUE);
		SetUseLighting(TRUE);
	}
	DrawSphere3D(position, radius, 16, color, color, TRUE);
}
