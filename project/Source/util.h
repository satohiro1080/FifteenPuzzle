#pragma once
#include <stdint.h>
#include <DxLib.h>
#include <numeric>
#include <list>
#include <assert.h>
#include <string>

/// <summary>
/// 便利な関数！
/// </summary>
namespace Util
{
	inline uint64_t ToMask(int num)
	{
		uint64_t mask = 1;
		for (int i = 0; i < num; i++)
		{
			mask *= 2;
		}
		return mask;
	}

	/// <summary>
	/// 入れ替え（utiltyをインクルードするとstdに同じ関数があるらしい）
	/// </summary>
	/// <typeparam name="C">入れ替えるクラス</typeparam>
	/// <param name="a">入れ替えA</param>
	/// <param name="b">入れ替えB</param>
	template <class C>
	inline void Swap(C& a, C& b)
	{
		C tmp = a;
		a = b;
		b = tmp;
	}

	/// <summary>
	/// 0..255の値を0..1の値に収める
	/// </summary>
	/// <param name="num">値（0..255）</param>
	/// <returns>値（0..1）</returns>
	inline float ByteToRate(int num)
	{
		num = max(num, 0);
		num = min(num, 255);

		return num / 255.0f;
	}

	/// <summary>
	/// 0..1の値を0..255の値に広げる
	/// </summary>
	/// <param name="num">値（0..1）</param>
	/// <returns>値（0..255）</returns>
	inline int RateToByte(float num)
	{
		num = max(num, 0.0f);
		num = min(num, 1.0f);

		return (int)(num * 255.0f);
	}

	// x,y=y,xの前提により階段状になった表の、真ん中の線上の座標
	inline int TableCenter(int y, int max)
	{
		int ans = 0;
		int a = max;
		for (int i = 0; i < y; i++)
		{
			ans += a--;
		}
		return ans;
	}

	// enum同士のペアを添え字に変換
	// x,yとy,xは同じ結果が帰る
	inline int Pair(int x, int y, int max)
	{
		if (x < y)
		{
			Swap<int>(x, y);
		}

		return  TableCenter(y, max) + x - y;
	}

	//2点の座標から角度
	inline float Vec2ToRad(float Pos1X, float Pos1Y, float Pos2X, float Pos2Y, bool plus = true)
	{
		float rad;

		//atan2()関数：-π～πまでの角度を返す
		//arctanはtanの逆 tanは角度から辺の比が分かるが、arctanは辺の比から角度が分かる
		//a = tan(b)となるとき、b = arctan(a)   ※ x, y, r で表すと tan は y / x に対応する！
		//つまり、tan(b) の答えが辺の比 a (Y座標 / X座標)になると分かっているときに、角度 b を逆算するという操作をしてくれるのが arctan(a)
		//角度は弧度法で返す
		rad = atan2f(Pos2Y - Pos1Y, Pos2X - Pos1X);

		//degが負のとき2π増やして(一周回して)正にする
		if (rad < 0 && plus) {
			rad = rad + 2 * DX_PI_F;
		}

		return rad;
	}

	//(0,0)から点への角度
	inline float Vec2ToRad(float x, float y, bool plus = true)
	{
		return Vec2ToRad(0, 0, x, y, plus);
	}

	// 角度から単位ベクトル
	inline void RadToVec2(float angle, float* x, float* y)
	{
		*x = cosf(angle);
		*y = sinf(angle);
	}

	// リスト内全要素の平均
	template <class C>
	inline C Avg(const std::list<C>& values)
	{
		// 要素ゼロだったらデフォルト値
		if (values.size() == 0) return C();

		return std::accumulate(values.begin(), values.end(), C()) / static_cast<float>(values.size());
	}

	/// <summary>
	/// リスト内の全要素をブレンド
	/// </summary>
	/// <typeparam name="C">リストのクラス</typeparam>
	/// <param name="values">ブレンドするリスト</param>
	/// <param name="blendRates">各要素のブレンド率（valuesと同じ要素数にすること）</param>
	/// <returns>全要素をブレンドした値</returns>
	template <class C>
	inline C Blend(const std::list<C>& values, const std::list<float>& blendRates)
	{
		if (values.size() == 0) return C();

		int vCount = static_cast<int>(values.size());
		int rCount = static_cast<int>(blendRates.size());

		assert(vCount == rCount);

		float rSum = std::accumulate(blendRates.begin(), blendRates.end(), 0.0f);
		auto vItr = values.begin();
		auto rItr = blendRates.begin();

		C vBlend = C();

		while (vItr != values.end() && rItr != blendRates.end())
		{
			C value = *vItr;
			float rate = *rItr;

			vItr++;
			rItr++;

			C rV;

			if (rSum == 0)
				rV = value / static_cast<float>(rCount);
			else
				rV = value * rate / rSum;

			vBlend += rV;
		}

		return vBlend;
	}


	/// <summary>
	/// リストから添え字で要素取り出す
	/// </summary>
	/// <typeparam name="C">リストのクラス</typeparam>
	/// <param name="values">リスト</param>
	/// <param name="i">要素番号</param>
	/// <returns>リストのi番目の要素</returns>
	template <class C>
	inline const C& Get(const std::list<C>& values, int i)
	{
		assert(0 <= i && i < static_cast<int>(values.size()));
		return *std::next(values.begin(), i);
	}

	// value が a と b の間にあればtrue（a と b の大小関係はどちらでも）
	inline const bool IsInRange(float value, float a, float b)
	{
		bool ans1 = a <= value && value < b;
		bool ans2 = b <= value && value < a;

		return ans1 || ans2;
	}

	enum class SnapType
	{
		ROUND = 0,
		FLOOR,
	};

	/// <summary>
	/// 決められた値の倍数に値をスナップする（余ったら四捨五入）
	/// </summary>
	/// <param name="value">元の値</param>
	/// <param name="scale">スナップの単位</param>
	/// <returns>スナップされた値</returns>
	inline const float Snap(const float& value, const float& scale, SnapType snapType = SnapType::ROUND)
	{
		float ret = value;
		ret = ret / scale;
		switch (snapType)
		{
		case Util::SnapType::ROUND:
			ret = roundf(ret);
			break;
		case Util::SnapType::FLOOR:
			ret = floorf(ret);
			break;
		}
		ret = ret * scale;

		return ret;
	}

	/// <summary>
	/// 1 を div 分割するようにスナップ（余ったら切り捨て）3分割など小数にしにくいときに使う
	/// </summary>
	/// <param name="value">元の値</param>
	/// <param name="div">スナップの分割数</param>
	/// <returns>スナップされた値</returns>
	inline const float SnapDiv(const float& value, const float& div, SnapType snapType = SnapType::ROUND)
	{
		return Snap(value, 1.0f / div, snapType);
	}

	/// <summary>
	/// 一周を超えた角度を-π～+πに収める
	/// </summary>
	/// <param name="rad">角度（ラジアン）</param>
	/// <returns>-π～+πにした角度（ラジアン）</returns>
	inline const float FixedRad(const float& rad)
	{
		float ret = rad;

		while (ret < -DX_PI_F)
		{
			ret += DX_PI_F * 2.0f;
		}
		while (ret >= DX_PI_F)
		{
			ret -= DX_PI_F * 2.0f;
		}

		return ret;
	}

	/// <summary>
	/// 値を指定の桁数になるようゼロ埋めした文字列にする
	/// </summary>
	/// <param name="value">元の値</param>
	/// <param name="digit">桁数</param>
	/// <returns>ゼロ埋めされた文字列</returns>
	inline const std::string IntToZeroStr(const int& value, const int& digit)
	{
		std::string str = std::to_string(value);
		str.insert(0, digit - str.length(), '0');
		return str;
	}

	inline const float GetRandFloat(const float& min, const float& max)
	{
		return static_cast<float>(GetRand(static_cast<int>((max - min) * 1000))) / 1000.0f + min;
	}
}
