#include "stdafx.h"
#include "ChapterSelectScene.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Button.h"
#include "Engine.h"

#include "ChapterLoader.h"

ChapterSelectScene::ChapterSelectScene() {
	background = CreateObject();
	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/ChapterSelectScene/background.png");

	title = CreateObject();
	title->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/ChapterSelectScene/chapter-title.png");
	title->GetComponent<Transform>()
		->SetPosY(2.1f)
		->SetScale(0.5f, 0.5f);

	for (int i = 1; i <= 5; i++) {
		auto tmp = CreateObject();
		tmp->AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/ChapterSelectScene/chapter" + std::to_string(i) +".png");
		tmp->GetComponent<Transform>()
			->SetPos( -4.f + 2.f * (i - 1), -5.5f - 1.f * i)
			->SetScale(0.25f, 0.25f);
		tmp->AttachComponent<Button>()
			->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE)
			->SetNormalScale(0.25f, 0.25f)
			->SetHoverScale(0.26f, 0.26f)
			->SetPushedScale(0.255f, 0.255f);

		chapters.push_back(tmp);
	}

	chapters[0]->onClickExit = [=]() {
		RG2R_SceneM->ChangeScene(new ChapterLoader("Resources/Chapters/1"));
	};
}

ChapterSelectScene::~ChapterSelectScene() {
}

void ChapterSelectScene::OnUpdate()
{
	for (int i = 0; i < 5; i++) {
		if (chapters[i]->transform->GetPos().y < -0.6f) {
			chapters[i]->transform->Translate(0, 0.1f);
		}
		else {
			chapters[i]->transform->SetPosY(-0.6f);
		}
	}

	titleAnimation += RG2R_TimeM->GetDeltaTime() * 50;

	title->transform->SetPosY(2.1f + Sin(titleAnimation) / 15);
}
