#pragma once
#include "Scene.h"

#include <vector>

class ChapterSelectScene :
	public Scene
{
private:
	float titleAnimation = 0;

private:
	Object* background;
	Object* title;
	
	std::vector<Object*> chapters;

public:
	ChapterSelectScene();
	~ChapterSelectScene();

	void OnUpdate();
};

