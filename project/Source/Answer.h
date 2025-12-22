#pragma once
#include "../Library/GameObject.h"

class MouseInputManager;
class GameManager;
class Board;

class Answer : public GameObject
{
public:
	Answer();
	~Answer();
	void Update() override;
	void Draw() override;

	void GetBoard(Board* _board) { board = _board; };

	enum COLOR_TYPE
	{
		RED = 0,
		GREEN,
		BLUE,
	};


private:
	static const int MAX_BOX_NUM = 3;
	struct ANSWER_BOX
	{
		int frameHandler;
		int backHandler;
		VECTOR2 position;	// 座標
		float exRate;		// 拡大率
		float shutterExRate;
		float animTime;		// 拡縮アニメーション用
		int panelNum;		// 回答表示するために合致する必要のあるパネルの番号
		bool select;	// 選択可能かみる
		std::string text;

	};
	ANSWER_BOX answerBox[MAX_BOX_NUM];

	int shutter;

	MouseInputManager* mouseInput;
	Board* board;
	GameManager* gameManaer;
};