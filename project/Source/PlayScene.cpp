#include "PlayScene.h"
#include "Screen.h"
#include "Board.h"
#include"Frame.h"
#include "GameManager.h"
#include "Answer.h"
#include "Question.h"
#include "MouseInputManager.h"
#include "QuizManager.h"
#include "BoardMove.h"

namespace
{
	static const int TILE_SIZE = 20;
	static const int GRID_OFFSET = 100;
}

PlayScene::PlayScene()
{
	m_gameManager = new GameManager();
	new QuizManager();

	m_board = new Board();
	BoardMove* move = new BoardMove();
	move->SetBoardRef(m_board);

	m_frame = new Frame();
	m_frame->SetBoard(m_board);

	m_answer = new Answer();
	m_question = new Question();

	m_mouseInputManager = new MouseInputManager();

	m_cursorX = 0;
	m_cursorY = 0;

	m_pushed = false;
}

PlayScene::~PlayScene()
{
	delete m_board;
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}

	if (m_pushed == false)
	{
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			m_cursorX++;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			m_cursorX--;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			m_cursorY++;
		}
		if (CheckHitKey(KEY_INPUT_UP))
		{
			m_cursorY--;
		}
		if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_Z) || CheckHitKey(KEY_INPUT_RETURN))
		{
			m_board->Slide(m_cursorX, m_cursorY);
		}
	}

	m_pushed = CheckHitKeyAll();

	if (m_board->IsOutside(m_cursorX, m_cursorY))
	{
		m_cursorX = 0;
		m_cursorY = 0;
	}
	m_question->Update();
	m_frame->SetCursor(m_cursorX, m_cursorY);
}

void PlayScene::Draw()
{
	for (int y = 0; y < m_board->GetHeight(); y++)
	{
		for (int x = 0; x < m_board->GetWidth(); x++)
		{
			int num = m_board->Get(x, y);
			int color = (x == m_cursorX && y == m_cursorY) ?
				0xFF0000 :
				0xFFFFFF;

			if (num == m_board->GetBlankNum())
			{
				DrawFormatString(GRID_OFFSET + x * TILE_SIZE, GRID_OFFSET + y * TILE_SIZE, color, "_");
			}
			else
			{
				DrawFormatString(GRID_OFFSET + x * TILE_SIZE, GRID_OFFSET + y * TILE_SIZE, color, "%d", num);
			}
		}
	}
	m_frame->Draw();
	m_question->Draw();

	//=== MouseInputManagerテストコード ============
	DrawBox(400, 50, 400 + 100, 50 + 100, 0xFFFFFF, FALSE);

	if (m_mouseInputManager->IsClickArea(VECTOR2(400, 50), VECTOR2(100, 100)))
	{
		DrawString(100, 450, "クリックされました", 0xFFFFFF);
	}
	else if (m_mouseInputManager->IsMouseOverArea(VECTOR2(400, 50), VECTOR2(100, 100)))
	{
		DrawString(100, 450, "マウスオーバーされました", 0xFFFFFF);
	}
	//==============================================

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
