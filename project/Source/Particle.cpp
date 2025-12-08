#include "Particle.h"
#include "ParticleComponent.h"
#include "../Library/Time.h"

namespace Satohiro
{
	Particle::Particle()
	{
		Init(PlayParticleParam());
	}

	Particle::~Particle()
	{
	}

	void Particle::Init(const PlayParticleParam& param)
	{
		m_param = param;
		m_time = 0.0f;
		m_transform = Transform();
		m_alpha = param.alpha.GetInProgress(0.0f);

		GetGraphSizeF(m_param.imageHandle, &m_imageCenterX, &m_imageCenterY);
		m_imageCenterX *= 0.5f;
		m_imageCenterY *= 0.5f;
	}

	void Particle::Update()
	{
		m_time += Time::DeltaTime();
		if (m_time > m_param.lifeTime.Get()) {
			m_time = m_param.lifeTime.Get();
		}

		float progress = m_time / m_param.lifeTime.Get();
		m_transform.position = m_param.position.GetInProgress(progress);
		m_transform.rotation = m_param.rotation.GetInProgress(progress);
		m_transform.scale = m_param.scale.GetInProgress(progress);

		m_alpha = m_param.alpha.GetInProgress(progress);
	}

	void Particle::Draw()
	{
		if (m_param.imageHandle < 0) {
			return;
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_alpha * 255.0f));
		{
			DrawRotaGraph3F(
				m_transform.position.x,
				m_transform.position.y,
				m_imageCenterX,
				m_imageCenterY,
				m_transform.scale.x,
				m_transform.scale.y,
				m_transform.rotation.z,
				m_param.imageHandle,
				TRUE
			);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
