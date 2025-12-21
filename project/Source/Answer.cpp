#include "Answer.h"
#include "Screen.h"

#include "MouseInputManager.h"

namespace AnswerConfig
{
	VECTOR2 boxSize = VECTOR2(150.0f, 100.0f);
}

Answer::Answer()
{
	answerBox[RED].frameHandler = LoadGraph("data/texture/AnswerBoxRed3d.png");
	answerBox[RED].backHandler = LoadGraph("data/texture/AnswerBoxRed_Back.png");
	answerBox[RED].exRate = 1.0f;

	answerBox[GREEN].frameHandler = LoadGraph("data/texture/AnswerBoxGreen3d.png");
	answerBox[GREEN].backHandler = LoadGraph("data/texture/AnswerBoxGreen_Back.png");
	answerBox[GREEN].exRate = 1.0f;

	answerBox[BLUE].frameHandler = LoadGraph("data/texture/AnswerBoxBlue3d.png");
	answerBox[BLUE].backHandler = LoadGraph("data/texture/AnswerBoxBlue_Back.png");
	answerBox[BLUE].exRate = 1.0f;


	float ofset = 64.0f;
	// 基準点になる一番左のBox
	answerBox[RED].position = VECTOR2(ofset + AnswerConfig::boxSize.x / 2.0f, Screen::HEIGHT - Screen::HEIGHT / 4.0f + AnswerConfig::boxSize.y / 2.0f);
	answerBox[GREEN].position = VECTOR2(answerBox[RED].position.x + AnswerConfig::boxSize.x + ofset, Screen::HEIGHT - Screen::HEIGHT / 4.0f + AnswerConfig::boxSize.y / 2.0f);
	answerBox[BLUE].position = VECTOR2(answerBox[GREEN].position.x + AnswerConfig::boxSize.x + ofset, Screen::HEIGHT - Screen::HEIGHT / 4.0f + AnswerConfig::boxSize.y / 2.0f);

	for (int i = 0; i < MAX_BOX_NUM; i++)
	{
		answerBox[i].animTime = 0.0f;
	}

	mouseInput = nullptr;
}

Answer::~Answer()
{

}

void Answer::Update()
{
	if (mouseInput == nullptr)
	{
		mouseInput = FindGameObject<MouseInputManager>();
	}

	for (int i = 0; i < MAX_BOX_NUM; i++)
	{
		if (mouseInput->IsClickArea(answerBox[i].position - AnswerConfig:: boxSize / 2.0f,AnswerConfig::boxSize))
		{
			answerBox[i].position.y = answerBox[i].position.y - 50.0f;

			// ここで選択した配列番号を送るよ
			// 例:GameManager->GetAnswer(i); [配列番号 = 選択した番号]　になっているからこれだけでできるかも
		}

		if (mouseInput->IsMouseOverArea(answerBox[i].position - AnswerConfig::boxSize / 2.0f, AnswerConfig::boxSize))
		{
			answerBox[i].animTime += DX_PI_F / 60.0f;
			answerBox[i].exRate = answerBox[i].exRate + sinf(answerBox[i].animTime) / 100.0f;
		}
		else
		{
			answerBox[i].exRate = 1.0f;
			answerBox[i].animTime = 0.0f;
		}
	}
}

void Answer::Draw()
{
	// 回答選択肢の背景
	DrawRectRotaGraph3F(answerBox[RED].position.x, answerBox[RED].position.y, 0, 0, AnswerConfig::boxSize.x, AnswerConfig::boxSize.y,
		AnswerConfig::boxSize.x / 2.0f, AnswerConfig::boxSize.y / 2.0f, answerBox[RED].exRate, answerBox[RED].exRate, 0.0f, answerBox[RED].backHandler, TRUE);

	DrawRectRotaGraph3F(answerBox[GREEN].position.x, answerBox[GREEN].position.y, 0, 0, AnswerConfig::boxSize.x, AnswerConfig::boxSize.y,
		AnswerConfig::boxSize.x / 2.0f, AnswerConfig::boxSize.y / 2.0f, answerBox[GREEN].exRate, answerBox[GREEN].exRate, 0.0f, answerBox[GREEN].backHandler, TRUE);

	DrawRectRotaGraph3F(answerBox[BLUE].position.x, answerBox[BLUE].position.y, 0, 0, AnswerConfig::boxSize.x, AnswerConfig::boxSize.y,
		AnswerConfig::boxSize.x / 2.0f, AnswerConfig::boxSize.y / 2.0f, answerBox[BLUE].exRate, answerBox[BLUE].exRate, 0.0f, answerBox[BLUE].backHandler, TRUE);

	// 回答選択肢の枠組み
	DrawRectRotaGraph3F(answerBox[RED].position.x, answerBox[RED].position.y, 0, 0, AnswerConfig::boxSize.x, AnswerConfig::boxSize.y,
		AnswerConfig::boxSize.x / 2.0f, AnswerConfig::boxSize.y / 2.0f, answerBox[RED].exRate, answerBox[RED].exRate, 0.0f, answerBox[RED].frameHandler, TRUE);

	DrawRectRotaGraph3F(answerBox[GREEN].position.x, answerBox[GREEN].position.y, 0, 0, AnswerConfig::boxSize.x, AnswerConfig::boxSize.y,
		AnswerConfig::boxSize.x / 2.0f, AnswerConfig::boxSize.y / 2.0f, answerBox[GREEN].exRate, answerBox[GREEN].exRate, 0.0f, answerBox[GREEN].frameHandler, TRUE);

	DrawRectRotaGraph3F(answerBox[BLUE].position.x, answerBox[BLUE].position.y, 0, 0, AnswerConfig::boxSize.x, AnswerConfig::boxSize.y,
		AnswerConfig::boxSize.x / 2.0f, AnswerConfig::boxSize.y / 2.0f, answerBox[BLUE].exRate, answerBox[BLUE].exRate, 0.0f, answerBox[BLUE].frameHandler, TRUE);

	/*
	// 仮赤箱
	DrawBoxAA(answerBox[RED].position.x, answerBox[RED].position.y,
		answerBox[RED].position.x + AnswerConfig::boxSize.x, answerBox[RED].position.y + AnswerConfig::boxSize.y, GetColor(255, 0, 0), TRUE);

	// 仮緑箱
	DrawBoxAA(answerBox[GREEN].position.x, answerBox[GREEN].position.y,
		answerBox[GREEN].position.x + AnswerConfig::boxSize.x, answerBox[GREEN].position.y + AnswerConfig::boxSize.y, GetColor(0, 255, 0), TRUE);

	// 仮青箱
	DrawBoxAA(answerBox[BLUE].position.x, answerBox[BLUE].position.y,
		answerBox[BLUE].position.x + AnswerConfig::boxSize.x, answerBox[BLUE].position.y + AnswerConfig::boxSize.y, GetColor(0, 0, 255), TRUE);
		*/
}
