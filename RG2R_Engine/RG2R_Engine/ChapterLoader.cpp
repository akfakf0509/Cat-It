#include "stdafx.h"
#include "ChapterLoader.h"

#include "SpriteRenderer.h"
#include "Transform.h"

ChapterLoader::ChapterLoader(const std::string& path) {
	std::string line;
	std::ifstream chapter(path);

	if (!chapter.is_open()) {
		std::cout << "Can't load file : " << path << std::endl;
	}

	while (std::getline(chapter, line))
	{
		std::vector<std::string> line_splited;
		std::string line_spliting = "";

		for (char i : line) {
			if (i == ' ') {
				line_splited.push_back(line_spliting);
				line_spliting = "";
			}
			else {
				line_spliting += i;
			}
		}
		line_splited.push_back(line_spliting);

		int x = std::stoi(line_splited[0]) * 1.13f / 2;
		int y = std::stoi(line_splited[1]) * 1.13f / 2;
		std::string texture = line_splited[2];

		auto tmp = CreateObject();
		tmp->AttachComponent<SpriteRenderer>()
			->SetTexture(texture);
		tmp->transform
			->SetScale(0.5f, 0.5f)
			->SetPos(x, y);

		objs.push_back(tmp);
	}

	chapter.close();
}

ChapterLoader::~ChapterLoader() {
}
