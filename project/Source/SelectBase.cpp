#include "SelectBase.h"

SelectBase::SelectBase()
{
	state = WAIT;
}

void SelectBase::Update()
{
	int mouseInput = GetMouseInput();
	int x, y;

	GetMousePoint(&x, &y);
	mousePoint = Vector2((float)x, (float)y);

	switch (state)
	{
	case WAIT:
		if ((mouseInput & MOUSE_INPUT_LEFT) != 0) 
		{
			state = SELECTING;
		}
		break;
	case SELECTING:
		if ((mouseInput & MOUSE_INPUT_LEFT) == 0) 
		{
			state = END;
		}
		break;
	case END:
		if ((mouseInput & MOUSE_INPUT_LEFT) != 0)
		{
			state = WAIT;
		}
		break;
	}
}
