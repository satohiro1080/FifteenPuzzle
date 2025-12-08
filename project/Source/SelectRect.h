#pragma once
#include "SelectBase.h"

class SelectRect : public SelectBase
{
public:
	SelectRect();
	~SelectRect();
	void Update() override;
	void Draw() override;
	bool CollisionDot(const Vector2& dotPos) const override;
private:
	Vector2 start;
	Vector2 end;
};
