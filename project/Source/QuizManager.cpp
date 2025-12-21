#include "QuizManager.h"

QuizManager::QuizManager()
{
	LoadQuizDatas();
}

QuizManager::~QuizManager()
{
}

void QuizManager::LoadQuizDatas()
{
	m_quizDatas.clear();

	// 定数からデータ取得
	for (const Quiz::Data& quiz : Quiz::QUIZ_DATAS)
	{
		m_quizDatas.push_back(quiz);
	}
}

void QuizManager::ShuffleQuizQue()
{
	m_quizQue.clear();

	for (int i = 0; i < m_quizDatas.size(); i++)
	{
		m_quizQue.push_back(i);
	}

	// ここにシャッフルを追加予定
}

Quiz::Data QuizManager::GetNextQuiz()
{
	//if (m_quizDatas.empty()) return;
	if (m_quizQue.empty()) ShuffleQuizQue();

	// 順番リストの先頭から一個取り出す
	int id = m_quizQue.front();

	Quiz::Data data = GetQuizWithID(id);
	m_quizQue.pop_front();

	return data;
}

Quiz::Data QuizManager::GetQuizWithID(int id) const
{
	if (id >= m_quizDatas.size()) return Quiz::Data();

	return m_quizDatas[id];
}
