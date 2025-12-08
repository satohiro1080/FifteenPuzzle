#pragma once
#include "Particle.h"

namespace Satohiro
{
	class ParticleComponent
	{
	public:
		Particle* parent;

		virtual ~ParticleComponent() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void Draw() {}
	};
}