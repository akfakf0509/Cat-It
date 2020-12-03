#include "stdafx.h"
#include "ChapterMaker.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Effect.h"
#include "Engine.h"

ChapterMaker::ChapterMaker()
{
	background = CreateObject();
	background->AttachComponent<SpriteRenderer>()
		->SetTexture(background_paths[0]);

	navigation = CreateObject();
	navigation->AttachComponent<SpriteRenderer>()
		->SetTexture(tile_paths[0]);
	navigation->transform
		->SetScale(0.25f, 0.25f);
	navigation->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0.5f)));
}

ChapterMaker::~ChapterMaker()
{
}

void ChapterMaker::OnUpdate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_RIGHT) == KeyState::KEYSTATE_ENTER) {
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_LSHIFT) == KeyState::KEYSTATE_STAY) {
			if (background_index >= background_paths.size() - 1) {
				background_index = -1;
			}
			background->GetComponent<SpriteRenderer>()
				->SetTexture(background_paths[++background_index]);
		}
		else
		{
			if (tile_index >= tile_paths.size() - 1) {
				tile_index = -1;
			}
			navigation->GetComponent<SpriteRenderer>()
				->SetTexture(tile_paths[++tile_index]);
		}
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_LEFT) == KeyState::KEYSTATE_ENTER) {
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_LSHIFT) == KeyState::KEYSTATE_STAY) {
			if (background_index <= 0) {
				background_index = background_paths.size();
			}
			background->GetComponent<SpriteRenderer>()
				->SetTexture(background_paths[--background_index]);
		}
		else {
			if (tile_index <= 0) {
				tile_index = tile_paths.size();
			}
			navigation->GetComponent<SpriteRenderer>()
				->SetTexture(tile_paths[--tile_index]);
		}
	}

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_ENTER) {
		y++;
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_ENTER) {
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_LCONTROL) == KeyState::KEYSTATE_STAY) {
			std::ofstream chapter("Resources/Chapters/newChapter");

			chapter.write((background_paths[background_index]).c_str(), background_paths[background_index].size());

			for (auto i : objs) {
				std::string tile_s = "\n";

				tile_s += std::to_string((int)i->GetPos().x) + " ";
				tile_s += std::to_string((int)i->GetPos().y) + " ";
				tile_s += i->GetPath() + " ";
				tile_s += std::to_string(i->GetIsText());

				chapter.write(tile_s.c_str(), tile_s.size());
			}

			chapter.close();
		}
		else {
			y--;
		}
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_ENTER) {
		x++;
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_ENTER) {
		x--;
	}

	navigation->transform
		->SetPos(x * 1.13f / 4, y * 1.13f / 4);

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_SPACE) == KeyState::KEYSTATE_ENTER) {
		auto tmp = new Tile(x, y, tile_paths[tile_index], tile_index > 4);

		AttachObject(tmp);

		objs.push_back(tmp);
	}
}
