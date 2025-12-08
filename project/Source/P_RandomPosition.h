#pragma once
#include "ParticleComponent.h"
#include "util.h"

class P_RandomPosition : public Satohiro::ParticleComponent
{
public:
	P_RandomPosition(Vector3 min, Vector3 max)
	{
		m_min = min;
		m_max = max;
	}
	void Start() override
	{
		/*
		float x = Util::GetRandFloat(m_min.x, m_max.x);
		float y = Util::GetRandFloat(m_min.y, m_max.y);
		float z = Util::GetRandFloat(m_min.z, m_max.z);

		parent->transform.position = Vector3(x, y, z);
		*/
	}

private:
	Vector3 m_min;
	Vector3 m_max;
};
