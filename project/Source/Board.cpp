#include "Board.h"

namespace
{
	static const int GRID_WIDTH = 4;
	static const int GRID_HEIGHT = 4;
}

Board::Board()
{
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		std::vector<int> line;

		for (int x = 0; x < GRID_WIDTH; x++)
		{
			line.push_back(y * GRID_WIDTH + x);
		}

		m_grid.push_back(line);
	}
}

Board::~Board()
{
}

int Board::Get(int x, int y) const
{
    return m_grid[y][x];
}

int Board::GetWidth() const
{
	return GRID_WIDTH;
}

int Board::GetHeight() const
{
	return GRID_HEIGHT;
}

bool Board::Slide(int x, int y)
{
	// 周囲4マスに空きマスがあるか見て、あればスワップ
	static const int DIR_X[] =
	{
		1,
		0,
		-1,
		0
	};

	static const int DIR_Y[] =
	{
		0,
		1,
		0,
		-1
	};

	for (int i = 0; i < 4; i++)
	{
		int targetX = x + DIR_X[i];
		int targetY = y + DIR_Y[i];

		if (IsOutside(targetX, targetY)) continue;

		if (m_grid[targetY][targetX] == 0)
		{
			Swap(x, y, targetX, targetY);
			return true;
		}
	}

	return false;
}

void Board::Swap(int ax, int ay, int bx, int by)
{
	std::swap(m_grid[ay][ax], m_grid[by][bx]);
}

bool Board::IsOutside(int x, int y)
{
	if (x < 0) return true;
	if (x >= GRID_WIDTH) return true;
	if (y < 0) return true;
	if (y >= GRID_HEIGHT) return true;

	return false;
}

bool Board::IsCorrectPos(int panelNumber)
{
	int x, y;
	NumberToPos(panelNumber, x, y);

	return m_grid[y][x] == panelNumber;
}

void Board::NumberToPos(int number, int& refPosX, int& refPosY)
{
	if (GRID_WIDTH == 0) return;

	refPosX = number % GRID_WIDTH;
	refPosY = number / GRID_WIDTH;
}
