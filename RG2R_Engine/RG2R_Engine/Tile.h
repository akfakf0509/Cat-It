#pragma once
#include "Object.h"
class Tile :
	public Object
{
private:
	int x = 0, y = 0;
	std::string path = "";

public:
	Tile();
	~Tile();

	Tile* SetX(int);
	Tile* SetY(int);
	Tile* SetPos(int, int);

	Vec2F GetPos();
};

