#pragma once
#include "Scene.h"
class MainScene :
	public Scene
{
private:
	float catItAnimation = 0;

private:
	Object* background;
	Object* catit;
	Object* startText;

public:
	MainScene();
	~MainScene();

	void OnUpdate();
};
