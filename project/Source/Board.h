#pragma once
#include <vector>

class Board
{
public:
	Board();
	~Board();
	int Get(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;

	// ˆÚ“®•s”\‚È‚çfalse
	bool Slide(int x, int y);
	void Swap(int ax, int ay, int bx, int by);
	// ”ÍˆÍŠO‚È‚çtrue
	bool IsOutside(int x, int y);
private:
	std::vector<std::vector<int>> m_grid;
};
