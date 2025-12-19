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
}