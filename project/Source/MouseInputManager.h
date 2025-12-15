#pragma once
#include "../Library/GameObject.h"

class MouseInputManager : public GameObject
{
public:
	MouseInputManager();
	~MouseInputManager();
	void Update() override;
	void Draw() override;

	VECTOR2 GetCursorPos() const { return m_cursorPosition; }
	bool GetIsClick() const { return m_isClick; }

	/// <summary>
	/// ボタンUI用 矩形内をクリックしたか取得
	/// </summary>
	/// <param name="areaPos">矩形の始点(左上)</param>
	/// <param name="areaSize">矩形の大きさ</param>
	/// <returns>クリックしたらtrue</returns>
	bool IsClickArea(const VECTOR2& areaPos, const VECTOR2& areaSize) const;
private:
	VECTOR2 m_cursorPosition;
	bool m_isClick;
};