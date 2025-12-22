#pragma once
#include "../Library/GameObject.h"

class MouseInputManager;

class BoardMove : public GameObject
{
public:
	BoardMove();
	~BoardMove();
	void Update() override;
	void Draw() override;
private:
	MouseInputManager* m_input;
};