#include "Frame.h"

Frame::Frame()
{
	shuterS = ssSTOP;
}

Frame::~Frame()
{
}

void Frame::Update()
{
}

void Frame::Draw()
{
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DrawBox(SPACE_X + SQUARE_SIZE * j, SPACE_Y + SQUARE_SIZE * i, SPACE_X + SQUARE_SIZE * (j + 1), SPACE_Y + SQUARE_SIZE * (i + 1), GetColor(255, 255, 255), false);
		}
	}
}

void Frame::SetOpenShutter(float time)
{
}

void Frame::SetCloseShutter(float time)
{
}
