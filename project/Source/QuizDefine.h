#pragma once
#include <string>

namespace Quiz
{
	struct Data
	{
		Data() : Data(-1, "Question", "", "", "", "")
		{
		}

		Data(int id, std::string questionText, std::string panelImagePath, std::string answer0Text, std::string answer1Text, std::string answer2Text)
		{
			ID = id;
			QuestionText = questionText;
			PanelImagePath = panelImagePath;
			Answer0Text = answer0Text;
			Answer1Text = Answer1Text;
			Answer2Text = Answer2Text;
		}

		int ID;
		std::string QuestionText;
		std::string PanelImagePath;
		std::string Answer0Text;
		std::string Answer1Text;
		std::string Answer2Text;
	};

	static const Data QUIZ_DATAS[]
	{
		Data(0, "この山は何？",			"富士山Image.png",					"富士山0", "富士山1","富士山2"),
		Data(1, "この人物は誰？",		"ハギワラ先生Image.png",			"ハギワラ先生0", "ハギワラ先生1", "ハギワラ先生2"),
		Data(2, "「？」に入るのは何？",	"めっちゃすごい謎解きImage.png",	"めっちゃすごい謎解きAnswer0", "めっちゃすごい謎解きAnswer1", "めっちゃすごい謎解きAnswer2"),
	};
}