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

	// 移動可能なら移動する 移動不能ならfalse
	bool Slide(int x, int y);
	// aとbのパネルを入れ替える
	void Swap(int ax, int ay, int bx, int by);
	// 範囲外ならtrue
	bool IsOutside(int x, int y);
	// 指定番号(0～15)のパネルが正しい位置にあればtrue
	bool IsCorrectPos(int panelNumber);
	// 番号を座標に変換(0なら左上、1ならその右隣…)
	void NumberToPos(int number, int& refPosX, int& refPosY);
private:
	std::vector<std::vector<int>> m_grid;
};
