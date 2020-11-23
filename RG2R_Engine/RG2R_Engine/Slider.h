#pragma once
#include "Object.h"
class Slider :
	public Object
{
private:
	float perValue;
	float value;

	bool clickedOn = false;

private:
	Object* bar;
	Object* button;

public:
	std::function<void()> onValueChanged = []() {};

public:
	Slider();
	~Slider();

	void OnUpdate();

	Slider* SetValue(float);

	float GetValue();
};

