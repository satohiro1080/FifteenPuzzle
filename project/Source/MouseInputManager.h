#pragma once
#include "../Library/GameObject.h"

class MouseInputManager : public GameObject
{
public:
	MouseInputManager();
	~MouseInputManager();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// ※工事中！　　ボタンUI用 矩形内をクリックしたか取得
	/// </summary>
	/// <param name="areaPos">矩形の始点</param>
	/// <param name="areaSize">矩形の大きさ</param>
	/// <returns>クリックしたらtrue</returns>
	bool IsClickArea(const VECTOR2& areaPos, const VECTOR2& areaSize);

private:
	VECTOR2 m_cursorPosition;
	bool m_isClick;


};