#pragma once
#include "Object.h"
class ButtonObject :
	public Object
{
private:
	Object* text;

	bool clickedOn = false;

public:
	ButtonObject();
	~ButtonObject();

	void OnUpdate();
};

