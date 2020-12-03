#pragma once
#include "Object.h"
class Tile :
	public Object
{
private:
	Vec2F pos = { 0,0 };
	std::string path = "";
	bool isText = false;

public:
	Tile(int, int, const std::string&, bool);
	~Tile();

	void OnUpdate();

	Tile* SetX(int);
	Tile* SetY(int);
	Tile* SetPos(Vec2F);
	Tile* SetPos(int, int);
	Tile* SetIsText(bool);

	Tile* Translate(Vec2F);
	Tile* Translate(int, int);

	Vec2F GetPos();
	std::string GetPath();
	bool GetIsText();
};

