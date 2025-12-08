#pragma once
#include "util.h"
#include "vector.h"

namespace Satohiro
{
	class RandomRangeValue
	{
	public:
		void Set(float value)
		{
			min = value;
			max = value;
			ResetRand();
		}
		void SetRange(float minValue, float maxValue)
		{
			min = minValue;
			max = maxValue;
			ResetRand();
		}
		void ResetRand()
		{
			value = Util::GetRandFloat(min, max);
		}
		float Get() const
		{
			return value;
		}
	private:
		float value = 0.0f;
		float min = 0.0f;
		float max = 0.0f;
	};

	class ParticleValue
	{
	public:
		ParticleValue() = default;
		ParticleValue(float value)
		{
			Set(value);
		}
		void Set(float value)
		{
			start.Set(value);
			end.Set(value);
		}
		void SetStart(float value)
		{
			start.Set(value);
		}
		void SetStartRange(float minValue, float maxValue)
		{
			start.SetRange(minValue, maxValue);
		}
		void SetEnd(float value)
		{
			end.Set(value);
		}
		void SetEndRange(float minValue, float maxValue)
		{
			end.SetRange(minValue, maxValue);
		}
		float GetInProgress(float progress) const
		{
			float startValue = start.Get();
			float endValue = end.Get();
			return startValue + (endValue - startValue) * progress;
		}
	private:
		RandomRangeValue start;
		RandomRangeValue end;
	};

	class ParticleVector3
	{
	public:
		void Set(const Vector3& value)
		{
			x.Set(value.x);
			y.Set(value.y);
			z.Set(value.z);
		}
		void SetStart(const Vector3& value)
		{
			x.SetStart(value.x);
			y.SetStart(value.y);
			z.SetStart(value.z);
		}
		void SetStartRange(const Vector3& minValue, const Vector3& maxValue)
		{
			x.SetStartRange(minValue.x, maxValue.x);
			y.SetStartRange(minValue.y, maxValue.y);
			z.SetStartRange(minValue.z, maxValue.z);
		}
		void SetEnd(const Vector3& value)
		{
			x.SetEnd(value.x);
			y.SetEnd(value.y);
			z.SetEnd(value.z);
		}
		void SetEndRange(const Vector3& minValue, const Vector3& maxValue)
		{
			x.SetEndRange(minValue.x, maxValue.x);
			y.SetEndRange(minValue.y, maxValue.y);
			z.SetEndRange(minValue.z, maxValue.z);
		}
		Vector3 GetInProgress(float progress) const
		{
			return Vector3(
				x.GetInProgress(progress),
				y.GetInProgress(progress),
				z.GetInProgress(progress)
			);
		}
	private:
		ParticleValue x;
		ParticleValue y;
		ParticleValue z;
	};

	class PlayParticleParam
	{
	public:
		// パーティクルパラメータ
		int imageHandle = -1;
		RandomRangeValue lifeTime;

		ParticleVector3 position;
		ParticleVector3 rotation;
		ParticleVector3 scale;

		ParticleValue alpha = 1.0f;
	};
}
