#include "stdafx.h"
#include "Slider.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Button.h"
#include "Engine.h"

Slider::Slider() {
	bar = CreateChildObject();
	bar->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SlideBar.png");
	bar->GetComponent<Transform>()
		->SetAnchor(bar->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	bar->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_NONE);
	bar->onClickEnter = [=]() {
		Rect rect = bar->GetComponent<SpriteRenderer>()->GetVisibleArea();
		Vec2F distance = RG2R_InputM->GetMouseWorldPos() - bar->GetComponent<Transform>()->GetWorldPos();

		value = (rect.right / INCH_PER_DISTANCE / 2 * GetComponent<Transform>()->GetScale().x + distance.x) / (rect.right / INCH_PER_DISTANCE * GetComponent<Transform>()->GetScale().x);

		SetValue(value);

		clickedOn = true;
	};
	bar->onClickExit = [=]() {
		clickedOn = false;
	};

	button = bar->CreateChildObject();
	button->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/SlideButton.png");
	button->GetComponent<Transform>()
		->SetAnchor(button->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter());
	button->AttachComponent<Button>()
		->SetButtonEffectType(ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE);
	button->onClickEnter = [=]() {
		clickedOn = true;
	};
	button->onClickExit = [=]() {
		clickedOn = false;
	};
}

Slider::~Slider() {
}

void Slider::OnUpdate() {
	if (clickedOn) {
		Rect rect = bar->GetComponent<SpriteRenderer>()->GetVisibleArea();
		Vec2F distance = RG2R_InputM->GetMouseWorldPos() - bar->GetComponent<Transform>()->GetWorldPos();

		value = (rect.right / INCH_PER_DISTANCE / 2 * GetComponent<Transform>()->GetScale().x + distance.x) / (rect.right / INCH_PER_DISTANCE * GetComponent<Transform>()->GetScale().x);

		SetValue(value);
	}

	if (value != perValue) {
		onValueChanged();
	}

	perValue = value;
}

Slider* Slider::SetValue(float value) {
	if (value < 0) {
		value = 0;
	}
	else if (value > 1) {
		value = 1;
	}

	this->value = value;

	Rect rect = bar->GetComponent<SpriteRenderer>()->GetVisibleArea();

	button->GetComponent<Transform>()->SetPos(-rect.right / INCH_PER_DISTANCE / 2 + value * rect.right / INCH_PER_DISTANCE, 0);

	return this;
}

float Slider::GetValue() {
	return value;
}