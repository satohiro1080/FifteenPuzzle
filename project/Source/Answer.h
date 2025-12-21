#pragma once
#include "../Library/GameObject.h"

class MouseInputManager;
class GameManager;

class Answer : public GameObject
{
public:
	Answer();
	~Answer();
	void Update() override;
	void Draw() override;

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
		float animTime;		// 拡縮アニメーション用
		bool checkHit;		// マウスポインターが触れているか
		bool select;		// 選択状態を保存
	};
	ANSWER_BOX answerBox[MAX_BOX_NUM];

	MouseInputManager* mouseInput;

};