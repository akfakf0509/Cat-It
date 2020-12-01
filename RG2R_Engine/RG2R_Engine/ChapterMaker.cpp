#include "stdafx.h"
#include "ChapterMaker.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Effect.h"
#include "Engine.h"

ChapterMaker::ChapterMaker()
{
	navigation = CreateObject();
	navigation->AttachComponent<SpriteRenderer>()
		->SetTexture(paths[0]);
	navigation->transform
		->SetScale(0.5f, 0.5f);
	navigation->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0.5f)));
}

ChapterMaker::~ChapterMaker()
{
}

void ChapterMaker::OnUpdate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_RIGHT) == KeyState::KEYSTATE_ENTER) {
		if (index >= paths.size() - 1) {
			index = -1;
		}
		navigation->GetComponent<SpriteRenderer>()
			->SetTexture(paths[++index]);
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_LEFT) == KeyState::KEYSTATE_ENTER) {
		if (index <= 0) {
			index = paths.size();
		}
		navigation->GetComponent<SpriteRenderer>()
			->SetTexture(paths[--index]);
	}

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_ENTER) {
		y++;
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_ENTER) {
		y--;
	}
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_ENTER) {
		x++;
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_ENTER) {
		x--;
	}

	navigation->transform
		->SetPos(x * 1.13f / 2, y * 1.13f / 2);

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_SPACE) == KeyState::KEYSTATE_ENTER) {

	}
}
