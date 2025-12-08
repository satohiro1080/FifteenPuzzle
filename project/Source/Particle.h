#pragma once
#include "Transform.h"
#include "ParticleParam.h"

namespace Satohiro
{
	class ParticleManager;
	class ParticleComponent;

	class Particle
	{
	public:
		Particle();
		~Particle();
		void Init(const PlayParticleParam& param);
		void Update();
		void Draw();

		bool IsDead() const
		{
			return m_time >= m_param.lifeTime.Get();
		}
	private:
		PlayParticleParam m_param;
		Transform m_transform;
		float m_time = 0.0f;
		float m_alpha = 1.0f;
		float m_imageCenterX = 0.0f;
		float m_imageCenterY = 0.0f;
	};
}
