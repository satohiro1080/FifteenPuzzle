#include "TitleScene.h"
#include "ColorDot.h"

TitleScene::TitleScene()
{
	SetCameraPositionAndTarget_UpVecY(Vector3(0, 0, -300), Vector3(0, 0, 0));

	ColorDot3D* dot = new ColorDot3D();
	dot->SetPosition(Vector3(300, 300, 300));
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void TitleScene::Draw()
{
	DrawString(100, 300, "15パズルクイズ", GetColor(255, 255, 255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
