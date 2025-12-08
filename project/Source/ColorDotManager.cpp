#include "ColorDotManager.h"
#include "ColorDot.h"
#include "SelectRect.h"

namespace
{
	static const int DOT_COUNT = 2000;
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;
	static const int MARGIN = 50;
}

ColorDotManager::ColorDotManager()
{
	createDots3D();
	pSelect = nullptr;
}

ColorDotManager::~ColorDotManager()
{
}

void ColorDotManager::Update()
{
	if (pSelect == nullptr)
	{
		pSelect = FindGameObject<SelectBase>();
	}

	selectUpdate();
	colorUpdate();
}

void ColorDotManager::Draw()
{
}

void ColorDotManager::createDots2D()
{
	for (int i = 0; i < DOT_COUNT; i++) {
		ColorDot2D* dot = new ColorDot2D();
		dot->SetPosition(getRandomPosition2D());
		dots.push_back(dot);
	}
}

void ColorDotManager::createDots3D()
{
	for (int i = 0; i < DOT_COUNT; i++) {
		ColorDot3D* dot = new ColorDot3D();
		dot->SetPosition(getRandomPosition3D());
		dots.push_back(dot);
	}
}

Vector2 ColorDotManager::getRandomPosition2D() const
{
	float x = (float)(MARGIN + GetRand(SCREEN_WIDTH - MARGIN * 2));
	float y = (float)(MARGIN + GetRand(SCREEN_HEIGHT - MARGIN * 2));

	return Vector2(x, y);
}

Vector3 ColorDotManager::getRandomPosition3D() const
{
	float x = (float)(MARGIN + GetRand(SCREEN_WIDTH - MARGIN * 2) - SCREEN_WIDTH / 2);
	float y = (float)(MARGIN + GetRand(SCREEN_HEIGHT - MARGIN * 2) - SCREEN_HEIGHT / 2);
	float z = (float)(GetRand(300));

	return Vector3(x, y, z);
}

void ColorDotManager::selectUpdate()
{
	if (pSelect != nullptr && pSelect->StateValue != SelectBase::WAIT)
	{
		bool hit = false;
		for (ColorDotBase* dot : dots)
		{
			if (pSelect->CollisionDot(dot->GetPosition()))
			{
				dot->IsSelected = true;
				hit = true;
			}
			else
			{
				dot->IsSelected = false;
			}
		}
	}
	else
	{
		for (ColorDotBase* dot : dots) {
			dot->IsSelected = false;
		}
	}
}

void ColorDotManager::colorUpdate()
{
	if (CheckHitKey(KEY_INPUT_D))
	{
		if (not pushing)
		{
			for (ColorDotBase* dot : dots)
			{
				if (dot->IsSelected)
				{
					dot->SetColorIndexToNext();
				}
			}
		}

		pushing = true;
	}
	else
	{
		pushing = false;
	}
}
