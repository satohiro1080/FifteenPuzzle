#pragma once
#include "ParticleComponent.h"
#include <DxLib.h>

class P_DrawBox : public Satohiro::ParticleComponent
{
public:
	void Draw() override
	{
		/*
		DrawBox(
			(int)parent->transform.position.x,
			(int)parent->transform.position.y,
			(int)(parent->transform.position.x + parent->transform.scale.x),
			(int)(parent->transform.position.y + parent->transform.scale.y),
			GetColor(255, 255, 255),
			1
		);
		*/
	}
};

