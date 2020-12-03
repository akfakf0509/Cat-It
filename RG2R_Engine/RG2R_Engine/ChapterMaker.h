#pragma once
#include "Scene.h"

#include <string>
#include <fstream>
#include <vector>

#include "Tile.h"

class ChapterMaker :
	public Scene
{
private:
	int background_index = 0;

	std::vector<std::string> background_paths{
		"Resources/Sprites/Chapter1/Background.png",
		"Resources/Sprites/Chapter2/Background.png"
	};

	int tile_index = 0;

	std::vector<std::string> tile_paths{
		"Resources/Sprites/Chapter1/Tile.png",
		"Resources/Sprites/Chapter2/Apple.png",
		"Resources/Sprites/Chapter2/Leaf.png",
		"Resources/Sprites/Chapter2/Wood.png",
		"Resources/Sprites/Chapter3/Cloud/tile-cloud5.png",
		"Resources/Sprites/RecycleBlock/Text/Cat.png",
		"Resources/Sprites/RecycleBlock/Text/Is.png",
		"Resources/Sprites/Chapter1/Text/Strong.png",
		"Resources/Sprites/Chapter1/Text/Weak.png",
		"Resources/Sprites/Chapter2/Text/Apple.png",
		"Resources/Sprites/Chapter2/Text/Leaf.png",
		"Resources/Sprites/Chapter2/Text/Win.png",
		"Resources/Sprites/Chapter3/Text/Can.png",
		"Resources/Sprites/Chapter3/Text/Earth.png",
		"Resources/Sprites/Chapter3/Text/Jump.png",
		"Resources/Sprites/Chapter3/Text/Sky.png"
	};

	std::vector<Tile*> objs;

private:
	int x = 0, y = 0;
	Object* background;
	Object* navigation;

public:
	ChapterMaker();
	~ChapterMaker();

	void OnUpdate();
};

