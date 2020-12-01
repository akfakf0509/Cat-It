#pragma once
#include "Scene.h"

#include <fstream>
#include <vector>

class ChapterMaker :
	public Scene
{
private:
	int index = 0;

	std::vector<std::string> paths{
		"Resources/Sprites/RecycleBlock/Cat.png",
		"Resources/Sprites/RecycleBlock/Is.png",
		"Resources/Sprites/Chapter1/Strong.png",
		"Resources/Sprites/Chapter1/Tile.png",
		"Resources/Sprites/Chapter1/Weak.png"
	};

	std::vector<Object*> objs;

private:
	int x = 0, y = 0;
	Object* navigation;

public:
	ChapterMaker();
	~ChapterMaker();

	void OnUpdate();
};

