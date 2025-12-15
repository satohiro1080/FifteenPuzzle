#include "Board.h"
#include <unordered_map>
#include <DxLib.h>
#include <random>

namespace
{
	static const int GRID_WIDTH = 4;
	static const int GRID_HEIGHT = 4;
	static const int GRID_COUNT = GRID_WIDTH * GRID_HEIGHT;
	static const int BLANK_NUM = 15;
}

Board::Board()
{
	Shuffle();
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

int Board::GetBlankNum() const
{
	return BLANK_NUM;
}

void Board::Shuffle()
{
	m_grid.clear();

	std::vector<int> numbers;
	for (int i = 0; i < GRID_COUNT - 1; i++)
	{
		numbers.push_back(i);
	}

	// 乱数生成器の準備
	std::random_device rd;
	std::mt19937 g(rd());

	// 配列をシャッフル（並べ替え）
	std::shuffle(numbers.begin(), numbers.end(), g);

	// 二次元配列に変換
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		std::vector<int> line;

		for (int x = 0; x < GRID_WIDTH; x++)
		{
			// 右下は空白
			if (numbers.empty())
			{
				line.push_back(BLANK_NUM);
			}
			else
			{
				line.push_back(numbers.back());
				numbers.pop_back();
			}
		}

		m_grid.push_back(line);
	}
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

		if (m_grid[targetY][targetX] == BLANK_NUM)
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
