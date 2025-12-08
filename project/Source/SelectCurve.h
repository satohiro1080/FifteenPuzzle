#pragma once
#include "SelectBase.h"
#include <list>

class SelectCurve : public SelectBase
{
public:
	SelectCurve();
	~SelectCurve();
	void Update() override;
	void Draw() override;
	bool CollisionDot(const Vector2& dotPos) const override;
private:
	std::list<Vector2> points;
	void pointUpdate();
};

