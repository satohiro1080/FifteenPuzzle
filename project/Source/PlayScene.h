#pragma once
#include "../Library/SceneBase.h"

class Board;
class Frame;
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	Board* m_board;
	Frame* m_frame;
	int m_cursorX;
	int m_cursorY;

	bool m_pushed;
};
