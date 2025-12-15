#include "Answer.h"
#include "Screen.h"

namespace AnswerConfig
{
	VECTOR2 boxSize = VECTOR2(150.0f, 100.0f);
}

Answer::Answer()
{
	float ofset = 64.0f;
	// äÓèÄì_Ç…Ç»ÇÈàÍî‘ç∂ÇÃBox
	answerBox[0].position = VECTOR2(ofset, Screen::HEIGHT - Screen::HEIGHT / 4.0f);
	answerBox[1].position = VECTOR2(answerBox[0].position.x + AnswerConfig::boxSize.x + ofset, Screen::HEIGHT - Screen::HEIGHT / 4.0f);
	answerBox[2].position = VECTOR2(answerBox[1].position.x + AnswerConfig::boxSize.x + ofset, Screen::HEIGHT - Screen::HEIGHT / 4.0f);
}

Answer::~Answer()
{

}

void Answer::Update()
{
	for (int i = 0; i < MAX_BOX_NUM; i++)
	{
		if (answerBox[i].checkHit)
		{
			answerBox[i].position.y = answerBox[i].position.y + 50.0f;
		}
	}
}

void Answer::Draw()
{
	// âºê‘î†
	DrawBoxAA(answerBox[0].position.x, answerBox[0].position.y,
		answerBox[0].position.x + AnswerConfig::boxSize.x, answerBox[0].position.y + AnswerConfig::boxSize.y, GetColor(255, 0, 0), TRUE);

	// âºóŒî†
	DrawBoxAA(answerBox[1].position.x, answerBox[1].position.y,
		answerBox[1].position.x + AnswerConfig::boxSize.x, answerBox[1].position.y + AnswerConfig::boxSize.y, GetColor(0, 255, 0), TRUE);

	// âºê¬î†
	DrawBoxAA(answerBox[2].position.x, answerBox[2].position.y,
		answerBox[2].position.x + AnswerConfig::boxSize.x, answerBox[2].position.y + AnswerConfig::boxSize.y, GetColor(0, 0, 255), TRUE);
}
