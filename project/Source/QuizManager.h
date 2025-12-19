#pragma once
#include "QuizDefine.h"
#include <vector>
#include <list>

// 全問題のデータを管理する
// 基本は GetNextQuiz() から問題を取得してね
// もしかしたら生成場所コモンシーンにするかも
class QuizManager
{
public:
	QuizManager();
	~QuizManager();

	// クイズの順番をシャッフルする
	void ShuffleQuizQue();

	// 次のクイズを取得
	// 一度出たクイズは、次にシャッフルされるまで出ない
	// 全てのクイズが出た状態でこの関数を呼ぶと、シャッフルされる
	Quiz::Data GetNextQuiz();

	// クイズの順番を無視して、指定IDのクイズを取得
	Quiz::Data GetQuizWithID(int id) const;
private:
	std::vector<Quiz::Data> m_quizDatas; // クイズのデータ
	std::list<int> m_quizQue;	// クイズの順番リスト
};
