#pragma once
#include <DxLib.h>
#include "../Library/myDxLib.h"
#include <string>

//概要
//＊2軸のベクトル
//＊正規化、長さ取得など便利な機能あり
//＊演算子を定義することで、ベクトルの足し算やスケーリングが簡単に
//＊dxlibのVECTOR構造体とは自動相互変換可能(VTransformなどVECTORを引数にした関数にVector3を突っ込んでもOK)
class Vector2
{
public:
	float x;	// x座標
	float y;	// y座標

	//▼コンストラクタ

	// x,yを0で初期化
	Vector2();

	// 引数でx,yを初期化
	Vector2(float _xy);

	// 引数でx,yを初期化
	Vector2(float _x, float _y);

	// dxlibのVECTOR構造体からVector2への変換
	// VECTORをVector2に代入しようとすると、このコンストラクタで暗黙的に変換してくれる
	Vector2(const VECTOR& v);
	Vector2(const VECTOR2& v);

	//▼変換

	// Vector2からdxlibのVECTOR構造体への変換
	// Vector2にVECTORを代入しようとすると、この演算子で暗黙的に変換してくれる
	operator const VECTOR() const;
	operator const VECTOR2() const;

	// ifの条件やbool変数にVector2を入れられる
	// その場合、ベクトルの大きさが0でなければtrueとして扱う
	operator bool() const;

	// 逆のベクトル
	const Vector2 operator-() const;

	//▼計算

	// ベクトルの足し算、dxlibのVAddと同等
	// a,bというベクトルがあるとすると、a + b == Vector2(a.x + b.x, a.y + b.y)
	const Vector2 operator+(const Vector2& value) const;

	// ベクトルの引き算、dxlibのVSubと同等
	// a, bというベクトルがあるとすると、a - b == Vector2(a.x - b.x, a.y - b.y)
	const Vector2 operator-(const Vector2& value) const;

	// ベクトルの各軸で掛け算
	// a,bというベクトルがあるとすると、a * b == Vector2(a.x * b.x, a.y * b.y)
	const Vector2 operator*(const Vector2& value) const;

	// ベクトルの各軸で割り算
	// a,bというベクトルがあるとすると、a / b == Vector2(a.x / b.x, a.y / b.y)
	const Vector2 operator/(const Vector2& value) const;

	// ベクトルのスケーリング、dxlibのVScaleと同等
	// ベクトルの各軸に同じ値を掛ける。
	// aというベクトル、bという値があるとすると、a * b == Vector2(a.x * b, a.y * b)
	const Vector2 operator*(float value) const;

	// ベクトルの各軸に同じ値で割る。
	// aというベクトル、bという値があるとすると、a / b == Vector2(a.x / b, a.y / b)
	const Vector2 operator/(float value) const;

	//▼イコール付きの計算

	// ベクトルの足し算、dxlibのVAddと同等
	// a,bというベクトルがあるとすると、a + b == Vector2(a.x + b.x, a.y + b.y)
	void operator+=(const Vector2& value);

	// ベクトルの引き算、dxlibのVSubと同等
	// a, bというベクトルがあるとすると、a - b == Vector2(a.x - b.x, a.y - b.y)
	void operator-=(const Vector2& value);

	// ベクトルの各軸で掛け算
	// a,bというベクトルがあるとすると、a * b == Vector2(a.x * b.x, a.y * b.y)
	void operator*=(const Vector2& value);

	// ベクトルの各軸で割り算
	// a,bというベクトルがあるとすると、a / b == Vector2(a.x / b.x, a.y / b.y)
	void operator/=(const Vector2& value);

	// ベクトルのスケーリング、dxlibのVScaleと同等
	// ベクトルの各軸に同じ値を掛ける。
	// aというベクトル、bという値があるとすると、a * b == Vector2(a.x * b, a.y * b)
	void operator*=(float value);

	// ベクトルの各軸に同じ値で割る。
	// aというベクトル、bという値があるとすると、a / b == Vector2(a.x / b, a.y / b)
	void operator/=(float value);

	//▼論理

	// 二つのベクトルの値が同じならtrue
	bool operator==(const Vector2& value) const;

	// 二つのベクトルの値が異なっていればtrue
	bool operator!=(const Vector2& value) const;

	//▼各種関数

	// ベクトルの長さを取得
	// dxlibのVSizeと同等
	float Size() const;

	// ベクトルの長さを取得する時、三平方の定理の、最後の平方根を取る部分を飛ばした値。つまり、長さの2乗の値
	// 長さを比較した結果は、長さの2乗を比較した結果と同じなので、球体当たり判定などで長さの比較があるとき代用可能
	// 平方根は結構重い処理なので、代用可能な場所ではSize()よりSquareSize()を使うのが好ましい(学生作品の規模なら誤差な気もするが)
	// dxlibのVSquareSizeと同等
	float SquareSize() const;

	// ベクトルの向きはそのまま、長さを1にしたベクトル(正規化ベクトル)を取得
	// ゼロベクトルを入れた場合ゼロベクトルを返す
	// dxlibのVNormと同等
	const Vector2 Norm() const;

	// iの値によって要素を取得（0 -> x, 1 -> y）
	// ループ処理で使用
	float Get(int i) const;

	// iの値によって要素にvalueをセット（0 -> x, 1 -> y）
	// ループ処理で使用
	void Set(int i, float value);

	std::string ToString() const;
};

//概要
//＊Vector2を補助する定数、関数
namespace V2
{
	//▼定数

	// ゼロベクトル
	static const Vector2 ZERO = Vector2(0.0f, 0.0f);

	// 全て1のベクトル
	// スケール周りでよく使う
	static const Vector2 ONE = Vector2(1.0f, 1.0f);

	//▼関数

	// 二つのベクトルの内積
	float Dot(const Vector2& a, const Vector2& b);

	// 二つのベクトルの外積
	float Cross(const Vector2& a, const Vector2& b);
};

//概要
//＊3軸のベクトル
//＊正規化、長さ取得など便利な機能あり
//＊演算子を定義することで、ベクトルの足し算やスケーリングが簡単に
//＊dxlibのVECTOR構造体とは自動相互変換可能(VTransformなどVECTORを引数にした関数にVector3を突っ込んでもOK)
class Vector3
{
public:
	float x;	// x座標
	float y;	// y座標
	float z;	// z座標

	//▼コンストラクタ

	// x,y,zを0で初期化
	Vector3();

	// 引数でx,y,zを初期化
	Vector3(float _xyz);

	// 引数でx,y,zを初期化
	Vector3(float _x, float _y, float _z);

	// dxlibのVECTOR構造体からVector3への変換
	// VECTORをVector3に代入しようとすると、このコンストラクタで暗黙的に変換してくれる
	Vector3(const VECTOR& v);

	//▼変換

	// Vector3からdxlibのVECTOR構造体への変換
	// Vector3にVECTORを代入しようとすると、この演算子で暗黙的に変換してくれる
	operator const VECTOR() const;

	// ifの条件やbool変数にVector3を入れられる
	// その場合、ベクトルの大きさが0でなければtrueとして扱う
	operator bool() const;

	//▼計算
	
	// 逆のベクトル
	const Vector3 operator-() const;

	// ベクトルの足し算、dxlibのVAddと同等
	// a,bというベクトルがあるとすると、a + b == Vector3(a.x + b.x, a.y + b.y, a.z + b.z)
	const Vector3 operator+(const Vector3& value) const;

	// ベクトルの引き算、dxlibのVSubと同等
	// a, bというベクトルがあるとすると、a - b == Vector3(a.x - b.x, a.y - b.y, a.z - b.z)
	const Vector3 operator-(const Vector3& value) const;

	// ベクトルの各軸で掛け算
	// a,bというベクトルがあるとすると、a * b == Vector3(a.x * b.x, a.y * b.y, a.z * b.z)
	// ベクトルからxz成分だけ取り出したい時に、vec * Vector3(1, 0, 1)って感じで使用
	const Vector3 operator*(const Vector3& value) const;

	// ベクトルの各軸で割り算
	// a,bというベクトルがあるとすると、a / b == Vector3(a.x / b.x, a.y / b.y, a.z / b.z)
	const Vector3 operator/(const Vector3& value) const;

	// ベクトルのスケーリング、dxlibのVScaleと同等
	// ベクトルの各軸に同じ値を掛ける。
	// aというベクトル、bという値があるとすると、a * b == Vector3(a.x * b, a.y * b, a.z * b)
	const Vector3 operator*(float value) const;

	// ベクトルの各軸に同じ値で割る。
	// aというベクトル、bという値があるとすると、a / b == Vector3(a.x / b, a.y / b, a.z / b)
	const Vector3 operator/(float value) const;

	//▼イコール付きの計算

	// ベクトルの足し算、dxlibのVAddと同等
	// a,bというベクトルがあるとすると、a + b == Vector3(a.x + b.x, a.y + b.y, a.z + b.z)
	void operator+=(const Vector3& value);

	// ベクトルの引き算、dxlibのVSubと同等
	// a, bというベクトルがあるとすると、a - b == Vector3(a.x - b.x, a.y - b.y, a.z - b.z)
	void operator-=(const Vector3& value);

	// ベクトルの各軸で掛け算
	// a,bというベクトルがあるとすると、a * b == Vector3(a.x * b.x, a.y * b.y, a.z * b.z)
	// ベクトルからxz成分だけ取り出したい時に、vec * Vector3(1, 0, 1)って感じで使用
	void operator*=(const Vector3& value);

	// ベクトルの各軸で割り算
	// a,bというベクトルがあるとすると、a / b == Vector3(a.x / b.x, a.y / b.y, a.z / b.z)
	void operator/=(const Vector3& value);

	// ベクトルのスケーリング、dxlibのVScaleと同等
	// ベクトルの各軸に同じ値を掛ける。
	// aというベクトル、bという値があるとすると、a * b == Vector3(a.x * b, a.y * b, a.z * b)
	void operator*=(float value);

	// ベクトルの各軸に同じ値で割る。
	// aというベクトル、bという値があるとすると、a / b == Vector3(a.x / b, a.y / b, a.z / b)
	void operator/=(float value);

	//▼論理

	// 二つのベクトルの値が同じならtrue
	bool operator==(const Vector3& value) const;

	// 二つのベクトルの値が異なっていればtrue
	bool operator!=(const Vector3& value) const;

	//▼各種関数

	// ベクトルの長さを取得
	// dxlibのVSizeと同等
	float Size() const;

	// ベクトルの長さを取得する時、三平方の定理の、最後の平方根を取る部分を飛ばした値。つまり、長さの2乗の値
	// 長さを比較した結果は、長さの2乗を比較した結果と同じなので、球体当たり判定などで長さの比較があるとき代用可能
	// 平方根は結構重い処理なので、代用可能な場所ではSize()よりSquareSize()を使うのが好ましい(学生作品の規模なら誤差な気もするが)
	// dxlibのVSquareSizeと同等
	float SquareSize() const;

	// ベクトルの向きはそのまま、長さを1にしたベクトル(正規化ベクトル)を取得
	// ゼロベクトルを入れた場合ゼロベクトルを返す
	// dxlibのVNormと同等
	const Vector3 Norm() const;

	// ベクトルに行列を適用
	// dxlibのVTransformと同等
	const Vector3 Transform(const MATRIX& mat) const;

	// iの値によって要素を取得（0 -> x, 1 -> y, 2 -> z）
	// ループ処理で使用
	float Get(int i) const;

	// iの値によって要素にvalueをセット（0 -> x, 1 -> y, 2 -> z）
	// ループ処理で使用
	void Set(int i, float value);

	std::string ToString() const;
};

//概要
//＊Vector3を補助する定数、関数
namespace V3
{
	//▼定数

	// ゼロベクトル
	static const Vector3 ZERO = Vector3(0.0f, 0.0f, 0.0f);

	// 全て1のベクトル
	// スケール周りでよく使う
	static const Vector3 ONE = Vector3(1.0f, 1.0f, 1.0f);

	//▼関数

	// 二つのベクトルの内積
	float Dot(const Vector3& a, const Vector3& b);

	// 二つのベクトルの外積
	Vector3 Cross(const Vector3& a, const Vector3& b);
};
