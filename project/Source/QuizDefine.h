#pragma once
#include <string>

namespace Quiz
{
	struct Data
	{
		Data() : Data(-1, "Question", "", "")
		{
		}

		Data(int id, std::string questionText, std::string panelImagePath, std::string answerImagePath)
		{
			ID = id;
			QuestionText = questionText;
			PanelImagePath = panelImagePath;
			AnswerImagePath = answerImagePath;
		}

		int ID;
		std::string QuestionText;
		std::string PanelImagePath;
		std::string AnswerImagePath;
	};

	static const Data QUIZ_DATAS[]
	{
		Data(0, "この山は何？",			"富士山Image.png",					"富士山Answer.png"),
		Data(1, "この人物は誰？",		"ハギワラ先生Image.png",			"ハギワラ先生Answer.png"),
		Data(2, "「？」に入るのは何？",	"めっちゃすごい謎解きImage.png",	"めっちゃすごい謎解きAnswer.png"),
	};
}