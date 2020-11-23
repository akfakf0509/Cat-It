#include "stdafx.h"
#include "MainScene.h"

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Transform.h"
#include "Engine.h"

#include "StageSelectScene.h"

MainScene::MainScene() {
	background = CreateObject();
	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Background.png");

	catit = CreateObject();
	catit->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/CatIt.png");

	startText = CreateObject();
	startText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"1HoonWhitecat")
		->SetText("Click to Start")
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER)
		->SetSize(64)
		->SetTextColor(Color(0, 0, 0, 0.5f));
	startText->transform->SetPosY(-2.5f);
}

MainScene::~MainScene() {
}

void MainScene::OnUpdate() {
	catItAnimation += RG2R_TimeM->GetDeltaTime() * 50;
	catit->transform->SetPosY(Sin(catItAnimation) / 4 + 0.3f);

	startText->GetComponent<TextRenderer>()
		->SetTextColor(Color(0, 0, 0, Sin(catItAnimation)));

	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT) {
		RG2R_SceneM->ChangeScene(new StageSelectScene());
	}
}