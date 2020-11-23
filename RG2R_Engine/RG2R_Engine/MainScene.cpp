#include "stdafx.h"
#include "MainScene.h"

#include "AnimationRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "BoxCollider.h"
#include "Button.h"
#include "Transform.h"
#include "RandomGenerator.h"
#include "Engine.h"

#include "PlayingSongName.h"
#include "Slider.h"

#include "PrologueScene.h"
#include "ProloguePuzzle.h"
#include "SickRoom.h"
#include "ProloguePuzzleCompelete.h"

MainScene::MainScene() {
	musicPaths.push_back("Ujabes - Kafka On The Shore");
	musicPaths.push_back("Ujabes - Love Cells");
	musicPaths.push_back("Ujabes - Violet Candle");

	musicLengths.push_back(152);
	musicLengths.push_back(118);
	musicLengths.push_back(161);

	backgrounnd = CreateObject();
	backgrounnd->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Background.jpg");
	backgrounnd->GetComponent<Transform>()
		->SetAnchor(backgrounnd->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());

	cat = CreateObject();
	cat->AttachComponent<AnimationRenderer>()
		->PushTextures("Resources/Sprites/CatAnimations/MainScene")
		->SetInterval(0.15f);
	cat->GetComponent<Transform>()
		->SetAnchor(cat->GetComponent<AnimationRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.7f, 0.7f)
		->SetPos(2.7f, 0.05f);

	startText = CreateObject();
	startText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Start")
		->SetSize(60)
		->SetTextColor(Color(72.f / 255, 59.f / 255, 59.f / 255))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	startText->AttachComponent<BoxCollider>()
		->SetArea(4.f, 0.5f);
	startText->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE);
	startText->GetComponent<Transform>()
		->SetPos(-6.f, 0.4f);
	startText->onClickExit = []() { 
		switch (std::stoi(RG2R_GameM->DataM->GetData("Scene")))
		{
		case 0:
			RG2R_SceneM->ChangeScene(new PrologueScene());
			break;
		case 1:
			RG2R_SceneM->ChangeScene(new ProloguePuzzle());
			break;
		case 2:
			RG2R_SceneM->ChangeScene(new SickRoom());
			break;
		case 3:
			RG2R_SceneM->ChangeScene(new ProloguePuzzleCompelete());
			break;
		default:
			RG2R_SceneM->ChangeScene(new PrologueScene());
			break;
		}
	};

	startImage = new Object();
	startImage->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Play.png");
	startImage->GetComponent<Transform>()
		->SetAnchor(startImage->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.08f, 0.07f)
		->SetPos(1.4f, 0);
	startText->AttachChild(startImage);

	settingText = CreateObject();
	settingText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Setting")
		->SetSize(60)
		->SetTextColor(Color(72.f / 255, 59.f / 255, 59.f / 255))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	settingText->AttachComponent<BoxCollider>()
		->SetArea(5.3f, 0.5f);
	settingText->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE);
	settingText->GetComponent<Transform>()
		->SetPos(-8.f, -0.2f);
	settingText->onClickExit = []() { RG2R_GameM->SettingM->SetIsEnable(true); };

	settingImage = new Object();
	settingImage->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Setting.png");
	settingImage->GetComponent<Transform>()
		->SetAnchor(settingImage->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.08f, 0.08f)
		->SetPos(1.8f, 0);
	settingText->AttachChild(settingImage);

	exitText = CreateObject();
	exitText->AttachComponent<TextRenderer>()
		->SetFontFamily(L"Sandoll 초록우산어린이")
		->SetText("Exit")
		->SetSize(60)
		->SetTextColor(Color(72.f / 255, 59.f / 255, 59.f / 255))
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_LEFT);
	exitText->AttachComponent<BoxCollider>()
		->SetArea(2.5f, 0.5f);
	exitText->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE);
	exitText->GetComponent<Transform>()
		->SetPos(-10.f, -0.8f);
	exitText->onClickExit = []() { RG2R_WindowM->Close(); };

	exitImage = new Object();
	exitImage->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Exit.png");
	exitImage->GetComponent<Transform>()
		->SetAnchor(settingImage->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.07f, 0.08f)
		->SetPos(1.1f, 0);
	exitText->AttachChild(exitImage);

	logo = CreateObject();
	logo->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/MainScene/Logo.png");

	logo->GetComponent<Transform>()
		->SetAnchor(logo->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
		->SetScale(0.5f, 0.5f)
		->SetPos(-2.8f, 2.f);

	playingSongName = new PlayingSongName();
	AttachObject(playingSongName);

	AttachObject(RG2R_GameM->SettingM);
}

MainScene::~MainScene() {
}

void MainScene::OnStart() {
	RG2R_GameM->SettingM->Load();
}

void MainScene::OnUpdate() {
	playTime -= RG2R_TimeM->GetDeltaTime();

	if (startText->GetComponent<Transform>()->GetPos().x < -4.4f) {
		startText->GetComponent<Transform>()->Translate(6.f * RG2R_TimeM->GetDeltaTime(), 0);
	}
	else {
		startText->GetComponent<Transform>()->SetPos(-4.3f, 0.4f);
	}

	if (settingText->GetComponent<Transform>()->GetPos().x < -4.4f) {
		settingText->GetComponent<Transform>()->Translate(6.f * RG2R_TimeM->GetDeltaTime(), 0);
	}
	else {
		settingText->GetComponent<Transform>()->SetPos(-4.3f, -0.2f);
	}
	
	if (exitText->GetComponent<Transform>()->GetPos().x < -4.4f) {
		exitText->GetComponent<Transform>()->Translate(6.f * RG2R_TimeM->GetDeltaTime(), 0);
	}
	else {
		exitText->GetComponent<Transform>()->SetPos(-4.3f, -0.8f);
	}

	if (playTime < 0) {
		RandomGenerator* randomGenerator = new RandomGenerator();
		int index = randomGenerator->GetInt(0, musicPaths.size() - 1);

		std::string songNameString = "Resources/Musics/" + musicPaths[index] + ".mp3";
		std::wstring songNameWstring;

		songNameWstring.assign(songNameString.begin(), songNameString.end());

		RG2R_GameM->MusicM->Play(songNameWstring);
		playTime = musicLengths[index];

		playingSongName->SetText(musicPaths[index]);
		playingSongName->commandLists[0]->Start();
	}

	if (perMousePos != RG2R_InputM->GetMouseWorldPos()) {
		cat->GetComponent<AnimationRenderer>()
			->SetInterval(0.1f);
	}
	else {
		cat->GetComponent<AnimationRenderer>()
			->SetInterval(0.15f);
	}

	perMousePos = RG2R_InputM->GetMouseWorldPos();

	//Object* object = playingSongName;

	//if (RG2R_InputM->GetKeyState(KeyCode::KEY_UP) == KeyState::KEYSTATE_STAY) {
	//	object->GetComponent<Transform>()->Translate(0, 0.05f);
	//}
	//if (RG2R_InputM->GetKeyState(KeyCode::KEY_DOWN) == KeyState::KEYSTATE_STAY) {
	//	object->GetComponent<Transform>()->Translate(0, -0.05f);
	//}
	//if (RG2R_InputM->GetKeyState(KeyCode::KEY_RIGHT) == KeyState::KEYSTATE_STAY) {
	//	object->GetComponent<Transform>()->Translate(0.05f, 0);
	//}
	//if (RG2R_InputM->GetKeyState(KeyCode::KEY_LEFT) == KeyState::KEYSTATE_STAY) {
	//	object->GetComponent<Transform>()->Translate(-0.05f, 0);
	//}

	//cout << object->GetComponent<Transform>()->GetPos().x << " " << object->GetComponent<Transform>()->GetPos().y << endl;
}