#pragma once
#include "../Library/GameObject.h"
#include <list>

class MouseInputManager : public GameObject
{
public:
	MouseInputManager();
	~MouseInputManager();
	void Update() override;
	void Draw() override;

	VECTOR2 GetCursorPos() const { return m_cursorPosition; }
	bool GetIsClick() const { return m_isClick; }

	//===↓↓↓=== 下の二つの関数は、元々constでしたが、デバッグ表示のために外しました ===

	/// <summary>
	/// ボタンUI用 矩形内をクリックしたか取得
	/// </summary>
	/// <param name="areaPos">矩形の始点(左上)</param>
	/// <param name="areaSize">矩形の大きさ</param>
	/// <returns>クリックしたらtrue</returns>
	bool IsClickArea(const VECTOR2& areaPos, const VECTOR2& areaSize);

	/// <summary>
	/// ボタンUI用 矩形内にカーソルがあるか取得
	/// </summary>
	/// <param name="areaPos">矩形の始点(左上)</param>
	/// <param name="areaSize">矩形の大きさ</param>
	/// <returns>カーソルがあればtrue</returns>
	bool IsMouseOverArea(const VECTOR2& areaPos, const VECTOR2& areaSize);
private:
	enum AreaState
	{
		NONE,
		MOUSE_OVER,
		CLICK,
	};

	struct Area
	{
		VECTOR2 pos;
		VECTOR2 size;
		AreaState state;
	};

	VECTOR2 m_cursorPosition;
	bool m_isClick;

	//=== デバッグ表示管理用 ===
	std::list<Area> m_currentFrameArea;

	void drawArea();
	void drawCursor();
};