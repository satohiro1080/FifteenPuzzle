#include "Question.h"

Question::Question()
{
	q_boardX = 50;
	q_boradY = 50;
	q_pushed = false;
	open = false;
	q_num = 0;
}

Question::~Question()
{
}

void Question::Update()
{
	if (q_pushed == false)
	{
		if (CheckHitKey(KEY_INPUT_N))
		{
			if (!open)
			{
				open = true;
			}
		}
		if (CheckHitKey(KEY_INPUT_M))
		{
			if (open)
			{
				open = false;
			}
		}
		if (CheckHitKey(KEY_INPUT_1))
		{
			if (!open)
			{
				q_num = 0;
			}
		}
		if (CheckHitKey(KEY_INPUT_2))
		{
			if (!open)
			{
				q_num = 1;
			}
		}
		if (CheckHitKey(KEY_INPUT_3))
		{
			if (!open)
			{
				q_num = 2;
			}
		}
	}

	q_pushed = CheckHitKeyAll();
}

void Question::Draw()
{
	if (open)
	{
		switch (q_num)
		{
		case 0:
			DrawBox(q_boardX, q_boradY, q_boardX + 600, q_boradY + 300, 0xffffff, TRUE);
			break;
		case 1:
			DrawBox(q_boardX, q_boradY, q_boardX + 600, q_boradY + 300, GetColor(255, 0, 0), TRUE);
			break;
		case 2:
			DrawBox(q_boardX, q_boradY, q_boardX + 600, q_boradY + 300, GetColor(0, 255, 0), TRUE);
			break;
		}

	}

}

void Question::SetOpenNo(bool _open, int _q_num)
{
	open = _open;
	q_num = _q_num;
}
