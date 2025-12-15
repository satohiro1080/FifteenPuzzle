#pragma once
#include"../Library/GameObject.h"

class Board;

class Frame : public GameObject {
public:
	Frame();
	~Frame();
	void Update()override;
	void Draw()override;

	//未実装
	void SetOpenShutter(float time);
	//未未実装
	void SetCloseShutter(float time);

	//枠1マスの大きさ(現状正方形だよ)
	int SquareSize() { return SQUARE_SIZE; }
	
	//カーソルの座標をセット
	void SetCursor(int x, int y) { cursor.x = x; cursor.y = y; }
	//ボードをセット
	void SetBoard(Board* b) { board = b; }
private:

	Board* board;

	static const int SPACE_X = 704;//枠の一番左上の頂点の座標_X
	static const int SPACE_Y = 104;//枠の一番左上の頂点の座標_Y
	static const int SQUARE_SIZE = 128;
	
	VECTOR2 cursor;

	static enum SHUTTER_STATE {
		ssSTOP = 0,
		ssOPEN,
		ssCLOSE,
	};
	SHUTTER_STATE shutterS;//ゲーム開始、終了後のシャッター

	float shutterTime;//何秒でシャッターを開け閉めするか
};
