#include "Frame.h"
#include"Board.h"
#include<unordered_map>
#include<string.h>

Frame::Frame()
{
	shutterTime = 0;
	shutterS = ssSTOP;
	board=nullptr;
	
	
	//board = new Board();
	
	
	std::string file = "data/quiz/";
	quizImage = LoadGraph("data/quiz/000.png");
	for (int i = 0; i < 15; i++) {
		std::string png ="t"+ std::to_string(i) + ".png";

		numImage[i]  = LoadGraph((file + png).c_str());
	}
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
			//ê≥ÇµÇ¢É}ÉXÇ…Ç†ÇÍÇŒìöÇ¶Ç™ï™Ç©ÇÈ
			if (correct && num != 15) {
				DrawBox(baseX, baseY, baseX + SQUARE_SIZE, baseY + SQUARE_SIZE, GetColor(0, 255, 0), true);
				int imaX = SQUARE_SIZE * x;
				int imaY = SQUARE_SIZE * y;
				DrawRectExtendGraph(baseX, baseY, baseX + SQUARE_SIZE, baseY + SQUARE_SIZE, imaX, imaY, SQUARE_SIZE, SQUARE_SIZE, quizImage, TRUE);
				DrawFormatString(baseX, baseY, GetColor(0, 255, 255), "%d", num);
			}
			//à·Ç§Ç»ÇÁêîéöâÊëú
			else if (num != 15) {
				DrawGraph(baseX, baseY, numImage[num], true);
			}
			
			
			DrawBox(SPACE_X, SPACE_Y, SPACE_X + SQUARE_SIZE * 4, SPACE_Y + SQUARE_SIZE * 4, GetColor(0, 0, 0), false);
			
			if (cursor.x == x && cursor.y == y) {
				DrawBox(baseX, baseY, baseX + SQUARE_SIZE, baseY + SQUARE_SIZE, GetColor(0, 0, 255), false);
			}
		}

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

void Frame::SetQuiz(int id)
{
	std::string file = "data/quiz/";
	std::string png = "00" + std::to_string(id) + ".png";
	quizImage = LoadGraph((file + png).c_str());
}
