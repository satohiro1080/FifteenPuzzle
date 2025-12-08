#pragma once
#include "../Library/GameObject.h"
#include "ParticleParam.h"

template<class C>
class Pool;

namespace Satohiro
{
	class Particle;

	class ParticleManager : public GameObject
	{
	public:
		ParticleManager();
		~ParticleManager();
		void Update() override;
		void Draw() override;
		
		Particle* CreateParticle(const PlayParticleParam& param);
		void CreateParticles(int count, const PlayParticleParam& param);
	private:
		Pool<Particle>* m_particles;
	};
}
