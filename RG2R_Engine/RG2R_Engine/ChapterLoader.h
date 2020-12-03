#pragma once
#include "Scene.h"

#include <fstream>
#include <map>

#include "Tile.h"

class ChapterLoader :
	public Scene
{
private:
	int x = 0, y = 0;

	Object* background;
	Object* player;

	std::map<int, std::map<int, Tile*>> objs;

public:
	ChapterLoader(const std::string&);
	~ChapterLoader();

	void OnUpdate();
};

