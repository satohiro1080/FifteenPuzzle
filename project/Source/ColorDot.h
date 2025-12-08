#pragma once
#include "vector.h"
#include "GetSet.h"
#include "../Library/GameObject.h"

class ColorDotBase : public GameObject
{
public:
	ColorDotBase();
	virtual ~ColorDotBase();
	void Update() override;
	virtual void Draw() override;

	const GetSet<float> Radius{ &radius };
	const Getter<int> Color{ &color };
	const Getter<int> ColorIndex{ &colorIndex };
	const GetSet<bool> IsSelected{ &isSelected };

	void SetColorIndex(int index);
	void SetColorIndexToNext();

	virtual Vector2 GetPosition() = 0;

protected:
	float radius;
	int color;
	int colorIndex;
	bool isSelected;
};

class ColorDot2D : public ColorDotBase
{
public:
	Vector2 GetPosition() override { return position; }
	void SetPosition(const Vector2& pos) { position = pos; }
private:
	Vector2 position;
};

class ColorDot3D : public ColorDotBase
{
public:
	void Draw() override;
	Vector2 GetPosition() override { return ConvWorldPosToScreenPos(position); }
	void SetPosition(const Vector3& pos) { position = pos; }
private:
	Vector3 position;
};
