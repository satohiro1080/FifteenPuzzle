#pragma once
#include "../Library/GameObject.h"
#include "GetSet.h"
#include "vector.h"

class SelectBase : public GameObject
{
public:
	enum State
	{
		DISABLE,
		WAIT,
		SELECTING,
		END
	};

	SelectBase();
	virtual ~SelectBase() {}
	virtual void Update() override;
	virtual void Draw() override {}
	virtual bool CollisionDot(const Vector2& dotPos) const = 0;
	void SetDisableState() { state = DISABLE; }
	void SetWaitState() { state = WAIT; }

	const Getter<State> StateValue{ &state };
protected:
	State state;
	Vector2 mousePoint;
};
