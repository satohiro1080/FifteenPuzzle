#pragma once
#include"../Library/GameObject.h"


enum SHUTTER_STATE {
	ssSTOP=0,
	ssOPEN,
	ssCLOSE,
};
class Frame : public GameObject {
public:
	Frame();
	~Frame();
	void Update()override;
	void Draw()override;

	void SetOpenShutter(float time);
	void SetCloseShutter(float time);
private:
	static const int SPACE_X = 704;
	static const int SPACE_Y = 104;
	static const int SQUARE_SIZE = 128;

	SHUTTER_STATE shuterS;

};
