#pragma once
#include "../Library/GameObject.h"

class MouseInputManager;
class Answer : public GameObject
{
public:
	Answer();
	~Answer();
	void Update() override;
	void Draw() override;


private:
	static const int MAX_BOX_NUM = 3;
	struct ANSWER_BOX
	{
		VECTOR2 position;	// 座標
		float exRate;		// 拡大率
		bool checkHit;		// マウスポインターが触れているか
		bool select;		// 選択状態を保存
	};
	ANSWER_BOX answerBox[MAX_BOX_NUM];

	MouseInputManager* mouseInput;

};