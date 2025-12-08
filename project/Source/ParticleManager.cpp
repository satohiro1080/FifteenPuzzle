#include "ParticleManager.h"
#include "Particle.h"
#include "Pool.h"

namespace Satohiro
{
	namespace
	{
		static const int MAX_PARTICLES = 1000;
	}

	ParticleManager::ParticleManager()
	{
		m_particles = new Pool<Particle>(MAX_PARTICLES);
	}

	ParticleManager::~ParticleManager()
	{
		delete m_particles;
	}

	void ParticleManager::Update()
	{
		m_particles->InvokeOnAll([](Pool<Particle>::PoolObject obj) {
			obj.object->Update();
			if (obj.object->IsDead()) {
				obj.inUse = false;
			}
			});
	}

	void ParticleManager::Draw()
	{
		m_particles->InvokeOnAll([](Pool<Particle>::PoolObject obj) {
			obj.object->Draw();
			});
	}

	Particle* ParticleManager::CreateParticle(const PlayParticleParam& param)
	{
		Pool<Particle>::PoolObject obj = m_particles->Create();
		obj.object->Init(param);
		return obj.object;
	}

	void ParticleManager::CreateParticles(int count, const PlayParticleParam& param)
	{
		for (size_t i = 0; i < count; i++)
		{
			Pool<Particle>::PoolObject obj = m_particles->Create();
			obj.object->Init(param);
		}
	}
}

