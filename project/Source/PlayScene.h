#pragma once
#include "../Library/SceneBase.h"

class Board;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	Board* m_board;
	int m_cursorX;
	int m_cursorY;

	bool m_pushed;
};
