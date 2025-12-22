#pragma once
#include "../Library/GameObject.h"

class MouseInputManager;
class Board;

class BoardMove : public GameObject
{
public:
	BoardMove();
	~BoardMove();
	void Update() override;
	void Draw() override;
	void SetBoardRef(Board* board) { m_board = board; }
private:
	MouseInputManager* m_input;
	Board* m_board;
};