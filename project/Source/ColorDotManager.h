#pragma once
#include <vector>
#include "../Library/GameObject.h"
#include "vector.h"

class ColorDotBase;
class SelectBase;

class ColorDotManager : public GameObject
{
public:
	ColorDotManager();
	~ColorDotManager();
	void Update() override;
	void Draw() override;

private:
	void createDots2D();
	void createDots3D();
	Vector2 getRandomPosition2D() const;
	Vector3 getRandomPosition3D() const;
	void selectUpdate();
	void colorUpdate();

	std::vector<ColorDotBase*> dots;
	SelectBase* pSelect;
	bool pushing;
};
