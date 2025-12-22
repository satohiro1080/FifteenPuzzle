#pragma once
#include <string>

namespace Quiz
{
	struct Data
	{
		Data() : Data(-1, "Question", "", "", "", "", 0)
		{
		}

		Data(int id, std::string questionText, std::string panelImagePath, std::string answer0Text, std::string answer1Text, std::string answer2Text, int correctAnswer)
		{
			ID = id;
			QuestionText = questionText;
			PanelImagePath = panelImagePath;
			Answer0Text = answer0Text;
			Answer1Text = answer1Text;
			Answer2Text = answer2Text;
			CorrectAnswer = correctAnswer;
		}

		int ID;
		std::string QuestionText;
		std::string PanelImagePath;
		std::string Answer0Text;
		std::string Answer1Text;
		std::string Answer2Text;
		int CorrectAnswer;
	};

	static const Data QUIZ_DATAS[]
	{
		Data(1, "この文字は何？",			"001.png",					"あ", "お","め", 0),
		Data(2, "アヒルは何匹いる？",		"002.png",			"1", "2", "3", 1),
		Data(3, "この画像は何でしょう？",	"003.png",	"アーツロゴ", "アモングアス", "ヒトデ", 1),
		Data(4, "アヒルは何匹いる？",	"004.png",	"3", "4", "5", 2),
		Data(5, "どこ？",	"005.png",	"北海道", "青森", "三重", 1),
	};
}