#include "BoardMove.h"
#include "MouseInputManager.h"
#include "Board.h"

BoardMove::BoardMove()
{
	m_input = nullptr;
	m_board = nullptr;
}

BoardMove::~BoardMove()
{
}

void BoardMove::Update()
{
	if (m_input == nullptr) m_input = FindGameObject<MouseInputManager>();
	if (m_input == nullptr) return;
	if (m_board == nullptr) return;

	static const int BOARD_X = 500;
	static const int BOARD_Y = 100;
	static const int PANEL_SIZE = 64;

	int x = 0;
	int y = 0;
	for (x = 0; x < 4; x++)
	{
		VECTOR2 pos = VECTOR2(BOARD_X + PANEL_SIZE * x, BOARD_Y);

		if (m_input->IsClickArea(pos, VECTOR2(PANEL_SIZE, PANEL_SIZE * 4)))
		{
			break;
		}
	}
	for (y = 0; y < 4; y++)
	{
		VECTOR2 pos = VECTOR2(BOARD_X, BOARD_Y + PANEL_SIZE * y);

		if (m_input->IsClickArea(pos, VECTOR2(PANEL_SIZE * 4, PANEL_SIZE)))
		{
			break;
		}
	}
	if (x >= 4) return;
	if (y >= 4) return;

	m_board->Slide(x, y);
}

void BoardMove::Draw()
{
}
