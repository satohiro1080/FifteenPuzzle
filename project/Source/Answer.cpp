#include "Answer.h"
#include "Screen.h"
#include "GameManager.h"
#include "MouseInputManager.h"
#include "Board.h"

namespace AnswerConfig
{
	VECTOR2 boxSize = VECTOR2(150.0f, 100.0f);
	float EXRATE = 1.25f;
	int RED_NUM = 0;
	int GREEN_NUM = 3;
	int BLUE_NUM = 12;
}

Answer::Answer()
{
	answerBox[RED].frameHandler = LoadGraph("data/texture/AnswerBoxRed3d.png");
	answerBox[RED].backHandler = LoadGraph("data/texture/AnswerBoxRed_Back.png");
	answerBox[RED].exRate = AnswerConfig::EXRATE;

	answerBox[GREEN].frameHandler = LoadGraph("data/texture/AnswerBoxGreen3d.png");
	answerBox[GREEN].backHandler = LoadGraph("data/texture/AnswerBoxGreen_Back.png");
	answerBox[GREEN].exRate = AnswerConfig::EXRATE;

	answerBox[BLUE].frameHandler = LoadGraph("data/texture/AnswerBoxBlue3d.png");
	answerBox[BLUE].backHandler = LoadGraph("data/texture/AnswerBoxBlue_Back.png");
	answerBox[BLUE].exRate = AnswerConfig::EXRATE;

	shutter = LoadGraph("data/texture/cloased.png");

	float ofset = 64.0f;
	// 基準点になる一番左のBox
	answerBox[RED].position = VECTOR2(ofset + AnswerConfig::boxSize.x / 2.0f, Screen::HEIGHT - Screen::HEIGHT / 4.0f + AnswerConfig::boxSize.y / 2.0f);
	answerBox[GREEN].position = VECTOR2(answerBox[RED].position.x + AnswerConfig::boxSize.x + ofset, Screen::HEIGHT - Screen::HEIGHT / 4.0f + AnswerConfig::boxSize.y / 2.0f);
	answerBox[BLUE].position = VECTOR2(answerBox[GREEN].position.x + AnswerConfig::boxSize.x + ofset, Screen::HEIGHT - Screen::HEIGHT / 4.0f + AnswerConfig::boxSize.y / 2.0f);

	answerBox[RED].panelNum = AnswerConfig::RED_NUM;
	answerBox[GREEN].panelNum = AnswerConfig::GREEN_NUM;
	answerBox[BLUE].panelNum = AnswerConfig::BLUE_NUM;

	answerBox[RED].text = "あああああ";
	answerBox[GREEN].text = "あああああ";
	answerBox[BLUE].text = "あああああ";

	for (int i = 0; i < MAX_BOX_NUM; i++)
	{
		answerBox[i].animTime = 0.0f;
		answerBox[i].select = false;
		answerBox[i].shutterExRate = 1.75f;
	}

	mouseInput = nullptr;
	board = nullptr;
}

Answer::~Answer()
{
	for (int i = 0; i < MAX_BOX_NUM; i++)
	{
		DeleteGraph(answerBox[i].backHandler);
		DeleteGraph(answerBox[i].frameHandler);
	}
}

void Answer::Update()
{
	if (mouseInput == nullptr)
	{
		mouseInput = FindGameObject<MouseInputManager>();
	}
	
	if (board == nullptr)
	{
		board = FindGameObject<Board>();
	}

	for (int i = 0; i < MAX_BOX_NUM; i++)
	{
		// 対象のパネルがハマったらセレクト可能にする
		if (board != nullptr)
		{
			if (board->IsCorrectPos(answerBox[i].panelNum))
			{
				answerBox[i].select = true;
			}
			else
			{
				answerBox[i].select = false;
			}
		}

		if (answerBox[i].select)
		{
			if (answerBox[i].shutterExRate >= 0.0f)
			{
				answerBox[i].shutterExRate -= 0.1f;
			}

			if (mouseInput->IsClickArea(answerBox[i].position - AnswerConfig::boxSize / 2.0f, AnswerConfig::boxSize))
			{
				//answerBox[i].position.y = answerBox[i].position.y - 50.0f;

				// ここで選択した配列番号を送るよ
				gameManaer->SetPlayerAnswer(i);
				// 例:GameManager->GetAnswer(i); [配列番号 = 選択した番号]　になっているからこれだけでできるかも
				break;
			}
		}
		else
		{
			if (answerBox[i].shutterExRate <= 1.75f)
			{
				answerBox[i].shutterExRate += 0.5f;
			}
		}

		if (mouseInput->IsMouseOverArea(answerBox[i].position - AnswerConfig::boxSize / 2.0f, AnswerConfig::boxSize))
		{
			answerBox[i].animTime += DX_PI_F / 30.0f;
			answerBox[i].exRate = answerBox[i].exRate + sinf(answerBox[i].animTime) / 100.0f;
		}
		else
		{
			answerBox[i].exRate = AnswerConfig::EXRATE;
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

	// 回答の画像表示
	DrawFormatString(answerBox[RED].position.x - 64.0f, answerBox[RED].position.y, GetColor(255, 255, 255), answerBox[RED].text.c_str());
	DrawFormatString(answerBox[GREEN].position.x - 64.0f, answerBox[GREEN].position.y, GetColor(255, 255, 255), answerBox[GREEN].text.c_str());
	DrawFormatString(answerBox[BLUE].position.x - 64.0f, answerBox[BLUE].position.y, GetColor(255, 255, 255), answerBox[BLUE].text.c_str());


	for (int i = 0; i < MAX_BOX_NUM; i++)
	{
		DrawRectRotaGraph3F(answerBox[i].position.x, answerBox[i].position.y - 55.0f, 0, 0, AnswerConfig::boxSize.x, AnswerConfig::boxSize.y,
			AnswerConfig::boxSize.x / 2.0f, AnswerConfig::boxSize.y / 2.0f, answerBox[i].exRate, answerBox[i].shutterExRate, 0.0f, shutter, TRUE);
	}

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
