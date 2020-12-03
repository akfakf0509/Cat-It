#include "stdafx.h"
#include "ChapterLoader.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"

#include "ChapterSelectScene.h"

ChapterLoader::ChapterLoader(const std::string& path) {
	background = CreateObject();
	background->AttachComponent<SpriteRenderer>();

	std::string line;
	std::ifstream chapter(path);

	if (!chapter.is_open()) {
		std::cout << "Can't load file : " << path << std::endl;
	}

	std::getline(chapter, line);
	background->GetComponent<SpriteRenderer>()
		->SetTexture(line);

	player = CreateObject();
	player->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/RecycleBlock/Player.png");
	player->transform
		->SetScale(0.5f / 4, 0.5f / 4);

	if (path == "Resources/Chapters/1") {
		x = -4;
	}
	else if (path == "Resources/Chapters/2") {
		x = -4;
		y = -9;
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

		int x = std::stoi(line_splited[0]);
		int y = std::stoi(line_splited[1]);
		std::string texture = line_splited[2];
		int isText = std::stoi(line_splited[3]);

		auto tmp = new Tile(x, y, texture, isText);

		AttachObject(tmp);

		objs[x][y] = tmp;
	}

	chapter.close();
}

ChapterLoader::~ChapterLoader() {
}

void ChapterLoader::OnUpdate() {
	bool strong = false;
	bool leafPlayer = false;

	for (auto i : objs) {
		for (auto j : i.second) {
			auto tmp = j.second;
			if (tmp != nullptr) {
				if (tmp->GetPath() == "Resources/Sprites/RecycleBlock/Text/Cat.png") {
					if (objs[tmp->GetPos().x + 2][tmp->GetPos().y] && objs[tmp->GetPos().x + 2][tmp->GetPos().y]->GetPath() == "Resources/Sprites/RecycleBlock/Text/Is.png") {
						if (objs[tmp->GetPos().x + 4][tmp->GetPos().y] && objs[tmp->GetPos().x + 4][tmp->GetPos().y]->GetPath() == "Resources/Sprites/Chapter1/Text/Strong.png") {
							strong = true;
						}
						else if (objs[tmp->GetPos().x + 4][tmp->GetPos().y] && objs[tmp->GetPos().x + 4][tmp->GetPos().y]->GetPath() == "Resources/Sprites/Chapter2/Text/Leaf.png") {
							leafPlayer = true;
						}
					}
					if (objs[tmp->GetPos().x][tmp->GetPos().y + 2] && objs[tmp->GetPos().x][tmp->GetPos().y + 2]->GetPath() == "Resources/Sprites/RecycleBlock/Text/Is.png") {
						if (objs[tmp->GetPos().x][tmp->GetPos().y + 4] && objs[tmp->GetPos().x][tmp->GetPos().y + 4]->GetPath() == "Resources/Sprites/Chapter1/Text/Strong.png") {
							strong = true;
						}
						else if (objs[tmp->GetPos().x][tmp->GetPos().y + 4] && objs[tmp->GetPos().x][tmp->GetPos().y + 4]->GetPath() == "Resources/Sprites/Chapter2/Text/Leaf.png") {
							leafPlayer = true;
						}
					}
				}

				if (leafPlayer && tmp->GetPath() == "Resources/Sprites/Chapter2/Leaf.png") {
					if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_ENTER) {
						objs[i.first][j.first + 1] = tmp;
						objs[i.first][j.first] = nullptr;
						tmp->Translate(0, 1);
					}
					else if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_ENTER) {
						objs[i.first][j.first - 1] = tmp;
						objs[i.first][j.first] = nullptr;
						tmp->Translate(0, -1);
					}
					if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_ENTER) {
						objs[i.first + 1][j.first] = tmp;
						objs[i.first][j.first] = nullptr;
						tmp->Translate(1, 0);
					}
					else if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_ENTER) {
						objs[i.first - 1][j.first] = tmp;
						objs[i.first][j.first] = nullptr;
						tmp->Translate(-1, 0);
					}

					if (objs[i.first + 1][j.first] && objs[i.first + 1][j.first]->GetPath() == "Resources/Sprites/Chapter2/Apple.png" ||
						objs[i.first - 1][j.first] && objs[i.first - 1][j.first]->GetPath() == "Resources/Sprites/Chapter2/Apple.png" ||
						objs[i.first][j.first + 1] && objs[i.first][j.first + 1]->GetPath() == "Resources/Sprites/Chapter2/Apple.png" ||
						objs[i.first][j.first - 1] && objs[i.first][j.first - 1]->GetPath() == "Resources/Sprites/Chapter2/Apple.png") {
						RG2R_SceneM->ChangeScene(new ChapterSelectScene());
					}
				}
			}
		}
	}

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_ENTER) {
		std::vector<Tile*> tmps;

		for (int i = x - 1; i < x + 2; i++) {
			for (int j = y; objs[i][j + 2] != nullptr; j += 2) {
				tmps.push_back(objs[i][j + 2]);
			}
		}

		bool block = false;

		for (auto i : tmps) {
			if (!i->GetIsText() && !strong) {
				block = true;
				break;
			}
		}

		if (!block) {
			for (auto i : tmps) {
				objs[i->GetPos().x][i->GetPos().y + 1] = i;
				objs[i->GetPos().x][i->GetPos().y] = nullptr;
				i->Translate(0, 1);
			}

			y++;
		}
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_ENTER) {
		std::vector<Tile*> tmps;

		for (int i = x - 1; i < x + 2; i++) {
			for (int j = y; objs[i][j - 2] != nullptr; j -= 2) {
				tmps.push_back(objs[i][j - 2]);
			}
		}

		bool block = false;

		for (auto i : tmps) {
			if (!i->GetIsText() && !strong) {
				block = true;
				break;
			}
		}

		if (!block) {
			for (auto i : tmps) {
				objs[i->GetPos().x][i->GetPos().y - 1] = i;
				objs[i->GetPos().x][i->GetPos().y] = nullptr;
				i->Translate(0, -1);
			}

			y--;
		}
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_ENTER) {
		std::vector<Tile*> tmps;

		for (int i = y - 1; i < y + 2; i++) {
			for (int j = x; objs[j + 2][i] != nullptr; j += 2) {
				tmps.push_back(objs[j + 2][i]);
			}
		}

		bool block = false;

		for (auto i : tmps) {
			if (!i->GetIsText() && !strong) {
				block = true;
				break;
			}
		}

		if (!block) {
			for (auto i : tmps) {
				objs[i->GetPos().x + 1][i->GetPos().y] = i;
				objs[i->GetPos().x][i->GetPos().y] = nullptr;
				i->Translate(1, 0);
			}

			x++;
		}
		player->SetIsFlipX(true);
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_ENTER) {
		std::vector<Tile*> tmps;

		for (int i = y - 1; i < y + 2; i++) {
			for (int j = x; objs[j - 2][i] != nullptr; j -= 2) {
				tmps.push_back(objs[j - 2][i]);
			}
		}

		bool block = false;

		for (auto i : tmps) {
			if (!i->GetIsText() && !strong) {
				block = true;
				break;
			}
		}

		if (!block) {
			for (auto i : tmps) {
				objs[i->GetPos().x - 1][i->GetPos().y] = i;
				objs[i->GetPos().x][i->GetPos().y] = nullptr;
				i->Translate(-1, 0);
			}

			x--;
		}
		player->SetIsFlipX(false);
	}

	if (objs[x + 2][y] && objs[x + 2][y]->GetPath() == "Resources/Sprites/Chapter2/Apple.png" ||
		objs[x - 2][y] && objs[x - 2][y]->GetPath() == "Resources/Sprites/Chapter2/Apple.png" ||
		objs[x][y + 2] && objs[x][y + 2]->GetPath() == "Resources/Sprites/Chapter2/Apple.png" ||
		objs[x][y - 2] && objs[x][y - 2]->GetPath() == "Resources/Sprites/Chapter2/Apple.png") {
		RG2R_SceneM->ChangeScene(new ChapterSelectScene());
	}

	player->transform
		->SetPos(Vec2F(x, y) * 1.13f / 4);

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER) {
		RG2R_SceneM->ChangeScene(new ChapterSelectScene());
	}
}