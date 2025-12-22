#pragma once
#include "../Library/GameObject.h"
#include "QuizDefine.h"

enum GAME_STATE
{
	GS_START,
	GS_ANSWERING,
	GS_ANSWER,
	GS_SWITCHING,
};


class QuizManager;
class Question;
class GameManager : public GameObject
{
public:
	GameManager();
	~GameManager();
	void Update()override;
	void Draw()override;
	//void SetQuiz(QuizManager* quizManager) { m_quizManager = quizManager; }
	void SetPlayerAnswer(int _answer);

	Quiz::Data GetQuiz() { return quiz; }
private:
	int answerNo;//プレイヤーの出した答え
	int correctAnswerNo;//問題の答え
	bool answer;//正解判定
	int quest_num;//問題番号
	int pushed;

	static const int ANSWER_NUMBER_1 = 2;//問題の答えの番号(仮)
	static const int ANSWER_NUMBER_2 = 0;//問題の答えの番号(仮)
	static const int ANSWER_NUMBER_3 = 1;//問題の答えの番号(仮)


	GAME_STATE g_state;
	Question* question;

	int displayTime = 0;
	int resultTime = 0;

	QuizManager* m_quizManager;   // ★ クイズ管理
	Quiz::Data quiz;
};