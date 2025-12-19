#pragma once
#include "../Library/GameObject.h"

enum GAME_STATE
{
	GS_START,
	GS_ANSWERING,
	GS_ANSWER,
	GS_SWITCHING,
};

enum QUESTION_NUMBER
{
	Q_NULL,
	Q_1,
	Q_2,
	Q_3
};

class Question;
class GameManager : public GameObject
{
public:
	GameManager();
	~GameManager();
	void Update()override;
	void Draw()override;


private:
	int answerNo;//プレイヤーの出した答え
	int correctAnswerNo;//問題の答え
	bool answer;//正解判定
	int quest_num;//問題番号
	int pushed;

	static const int ANSWER_NUMBER_1 = 3;//問題の答えの番号(仮)
	static const int ANSWER_NUMBER_2 = 1;//問題の答えの番号(仮)
	static const int ANSWER_NUMBER_3 = 2;//問題の答えの番号(仮)


	GAME_STATE g_state;
	Question* question;
	QUESTION_NUMBER q_num;
	int displayTime = 0;
	int resultTime = 0;



};