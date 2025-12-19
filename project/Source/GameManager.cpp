#include "GameManager.h"

GameManager::GameManager()
{
	displayTime = 300;
	resultTime = 120;

}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
	;
	switch (g_state)
	{
	case GS_START://ゲームの開始＆次の問題へ移動
		switch (q_num)
		{
		case Q_NULL:
			q_num = Q_1;
			correctAnswerNo = ANSWER_NUMBER_1;
			g_state = GS_ANSWERING;
			break;
		case Q_1:
			q_num = Q_2;
			correctAnswerNo = ANSWER_NUMBER_2;
			g_state = GS_ANSWERING;
			break;
		case Q_2:
			q_num = Q_3;
			correctAnswerNo = ANSWER_NUMBER_3;
			g_state = GS_ANSWERING;
			break;
		case Q_3:
			break;
		}
		break;
	case GS_ANSWERING://回答フェイズ
		if (pushed == false)
		{
			if (CheckHitKey(KEY_INPUT_Z))//回答1(仮)
			{
				answerNo = 1;
				g_state = GS_ANSWER;
			}
			if (CheckHitKey(KEY_INPUT_X))//回答2(仮)
			{
				answerNo = 2;
				g_state = GS_ANSWER;
			}
			if (CheckHitKey(KEY_INPUT_C))//回答3(仮)
			{
				answerNo = 3;
				g_state = GS_ANSWER;
			}
		}

		pushed = CheckHitKeyAll();

		break;
	case GS_ANSWER://正解発表
		if (resultTime > 0)
		{
			resultTime--;
		}
		else
		{
			resultTime = 0;
		}
		if (answerNo == correctAnswerNo)
		{
			answer = true;
			//resultTime--;
			if (displayTime > 0)
			{
				displayTime--;
			}
			else
			{
				g_state = GS_START;
				//answer = false;
				displayTime = 300;
				resultTime = 120;
			}
		}
		else
		{
			answer = false;
			//resultTime--;
			if (displayTime > 0)
			{
				displayTime--;
			}
			else
			{
				g_state = GS_START;
				//answer = false;
				displayTime = 300;
				resultTime = 120;
			}
		}
		break;

	}
}

void GameManager::Draw()
{
	if (g_state == GS_ANSWER)
	{
		if (resultTime <= 0)
		{
			if (answer)
			{
				DrawCircle(300, 200, 100, GetColor(255, 0, 0), false);
			}
			else
			{
				DrawLine(100, 100, 400, 400, GetColor(0, 0, 255), false);
				DrawLine(400, 100, 100, 400, GetColor(0, 0, 255), false);
			}
		}

	}


	DrawFormatString(50, 500, 0xffffff, "g_state = %d", g_state, true, false);
	DrawFormatString(50, 550, 0xffffff, "問%d", q_num, true, false);
	DrawFormatString(50, 600, 0xffffff, "正解発表まで%d", resultTime, true, false);
	DrawFormatString(50, 650, 0xffffff, "次の問題まで%d", displayTime, true, false);	
}
