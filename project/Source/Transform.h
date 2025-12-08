#pragma once
#include "vector.h"
#include <list>
#include <string>

//概要
//＊座標、回転、拡縮をまとめたクラス
//＊親を設定するとグローバル情報を取得する時親に影響された情報になる
//＊親子関係の参考：https://dkrevel.com/makegame-beginner/parent/
class Transform
{
public:
	Vector3 position;	// ローカル座標
	Vector3 rotation;	// ローカル回転(ラジアン)
	Vector3 scale;		// ローカル拡縮

	//▼コンストラクタ

	// 座標と回転に(0,0,0)、拡縮に(1,1,1)を入れて初期化。親はnullptr
	Transform();

	// 回転に(0,0,0)、拡縮に(1,1,1)を入れて初期化。親はnullptr
	Transform(const Vector3& _position);

	// 引数で座標、回転、拡縮を初期化。親はnullptr
	Transform(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale);

	// 引数で座標、回転、拡縮、親ポインタを初期化。
	Transform(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale, Transform* _parent);

	~Transform();

	//▼各種関数

	// 親の影響を含めたグローバル情報を取得(親のXが10、子のXが20だったら子のグローバル座標はX30、みたいな)
	// 親が未設定なら意味なし
	const Transform Global() const;

	// 自身の持つ座標、回転、拡縮情報から行列を取得
	// モデルの描画の時に使用
	const MATRIX Matrix() const;

	// 回転の行列だけ取得
	// キャラの向いてる方向をベクトルで欲しいときなどに使用
	const MATRIX RotationMatrix() const;

	// 回転を参照し、右を指す単位ベクトルを取得
	const Vector3 Right() const;

	// 回転を参照し、正面を指す単位ベクトルを取得
	const Vector3 Up() const;

	// 回転を参照し、上を指す単位ベクトルを取得
	const Vector3 Forward() const;

	// 回転を各軸0～2πの間に直して取得
	const Vector3 LimitedRotation() const;

	// カンマ区切り文字列化
	const std::string ToString() const;

	//▼ゲッター、セッター

	inline const Transform* Parent() const { return parent; }
	void SetParent(Transform* _parent);

	/// <summary>
	/// 指定したグローバルになるように、ローカルを変更する
	/// </summary>
	/// <param name="global">グローバル座標</param>
	void SetGlobal(const Transform& global);

	const Transform operator+(const Transform& trs) const;
	const Transform operator-(const Transform& trs) const;
	const Transform operator*(const float sca) const;
	const Transform operator/(const float sca) const;
	const Transform operator-() const;
	void operator+=(const Transform& trs);
	void operator-=(const Transform& trs);
	void operator*=(const float sca);
private:
	Transform* parent;	// 親トランスフォームのポインタ
	std::list<Transform*> children;	// 子トランスフォームのポインタのリスト

	// 子を追加
	inline void AddChild(Transform* child) { children.push_back(child); }
	// 子をリストから消す
	void RemoveChild(Transform* child);

	/// <summary>
	/// 親との連携を解除
	/// </summary>
	/// <param name="_parent">親のポインタ</param>
	/// <param name="removeFromChildren">親の子供リストから消す</param>
	void RemoveParent(Transform* _parent, bool removeFromChildren = true);
};
