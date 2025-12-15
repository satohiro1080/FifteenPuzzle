#include "Frame.h"
#include"Board.h"
#include<unordered_map>


Frame::Frame()
{
	shutterTime = 0;
	shutterS = ssSTOP;
	board=nullptr;
	
	
	//board = new Board();
}

Frame::~Frame()
{
}

void Frame::Update()
{
	switch (shutterS)
	{	
	case ssSTOP:
		break;
	case ssOPEN:
		break;
	case ssCLOSE:
		break;
	default:
		break;
	}
}

void Frame::Draw()
{
	SetFontSize(50);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int baseX = SPACE_X + SQUARE_SIZE * x;
			int baseY = SPACE_Y + SQUARE_SIZE * y;

			int num = board->Get(x, y);
			bool correct = board->IsCorrectPos(num);
			//ƒ}ƒX‚Æ”Ô†ˆê’v‚µ‚Ä‚½‚ç—Î
			if (correct && num != 15) {
				DrawBox(baseX, baseY, baseX + SQUARE_SIZE, baseY + SQUARE_SIZE, GetColor(0, 255, 0), true);
			}

			else if (num != 15) {
				DrawBox(baseX, baseY, baseX + SQUARE_SIZE, baseY + SQUARE_SIZE, GetColor(255, 0, 0), true);
			}
			if (num != 15) {
				DrawFormatString(baseX, baseY, GetColor(255, 255, 255), "%d", num);
			}

			if (cursor.x == x && cursor.y == y) {
				DrawBox(baseX, baseY, baseX + SQUARE_SIZE, baseY + SQUARE_SIZE, GetColor(0, 0, 255), false);
			}
			else {
				DrawBox(baseX, baseY, baseX + SQUARE_SIZE, baseY + SQUARE_SIZE, GetColor(255, 255, 255), false);
			}
		}
		//DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", board->Get(0,0));
	}
	SetFontSize(20);
}

void Frame::SetOpenShutter(float time)
{
	shutterTime = time;
	shutterS = ssOPEN;
}

void Frame::SetCloseShutter(float time)
{
	shutterTime = time;
	shutterS = ssCLOSE;
}
