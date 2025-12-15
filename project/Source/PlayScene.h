#pragma once
#include "../Library/SceneBase.h"

class Board;
class Frame;
class GameManager;
class Answer;
class Question;
class MouseInputManager;
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
	GameManager* m_gameManager;
	Answer* m_answer;
	Question* m_question;
	MouseInputManager* m_mouseInputManager;

	int m_cursorX;
	int m_cursorY;

	bool m_pushed;
};
