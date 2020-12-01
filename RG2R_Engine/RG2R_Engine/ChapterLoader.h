#pragma once
#include "Scene.h"

#include <fstream>
#include <vector>

class ChapterLoader :
	public Scene
{
private:
	std::vector<Object*> objs;

public:
	ChapterLoader(const std::string&);
	~ChapterLoader();
};

