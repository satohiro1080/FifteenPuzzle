#pragma once
#include "../Library/GameObject.h"

class Question : public GameObject
{
public:
	Question();
	~Question();
	void Update()override;
	void Draw()override;
	bool GetOpen() { return open; }
	void SetOpenNo(bool _open, int _q_num);


private:
	int q_boardX, q_boradY;
	bool q_pushed;
	bool open;
	int q_num;



};