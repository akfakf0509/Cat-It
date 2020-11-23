#include "stdafx.h"
#include "Button.h"

#include "Texture.h"
#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::OnStart() {
	transform = GetOwner()->GetComponent<Transform>();
	spriterenderer = GetOwner()->GetComponent<SpriteRenderer>();
	circleCollider = GetOwner()->GetComponent<CircleCollider>();
	boxcollider = GetOwner()->GetComponent<BoxCollider>();

	if (effectType == ButtonEffectType::BUTTONEFFECTTYPE_IMAGECHANGE) {
		if (spriterenderer == nullptr) {
			cout << "[" << GetOwner()->GetName() << "] " << "<Button> : Sprite Renderer is nullptr" << endl;
			SetIsEnable(false);
			return;
		}

		if (normalTexture == nullptr) {
			normalTexture = spriterenderer->GetTexture();
		}
		if (hoverTexture == nullptr) {
			hoverTexture = spriterenderer->GetTexture();
		}
		if (pushedTexture == nullptr) {
			pushedTexture = spriterenderer->GetTexture();
		}
	}
	else if (effectType == ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE) {
		if (normalScale == Vec2F(1, 1)) {
			normalScale = transform->GetScale();
		}
		if (hoverScale == Vec2F(1.1f, 1.1f)) {
			hoverScale = transform->GetScale() + Vec2F(0.1f, 0.1f);
		}
		if (pushedScale == Vec2F(1.05f, 1.05f)) {
			pushedScale = transform->GetScale() + Vec2F(0.05f, 0.05f);
		}
	}
}

void Button::OnUpdate() {
	Vec2F position = transform->GetWorldPos();
	Vec2F mouseposition = RG2R_InputM->GetMouseWorldPos();

	std::function<void()> checkMouseStat = [=]() {
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER) {
			StateUpdate(ButtonState::BUTTONSTATE_PUSHED);
			GetOwner()->OnClickEnter();
			ApplyListener(GetOwner()->onClickEnter);

			clickedOn = true;
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_STAY && clickedOn) {
			GetOwner()->OnClickStay();
			ApplyListener(GetOwner()->onClickStay);
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_NONE) {
			StateUpdate(ButtonState::BUTTONSTATE_HOVER);
		}
	};

	if (boxcollider != nullptr) {
		if (position.x - boxcollider->GetWidthSize() / 2 <= mouseposition.x && mouseposition.x <= position.x + boxcollider->GetWidthSize() / 2 &&
			position.y - boxcollider->GetHeightSize() / 2 <= mouseposition.y && mouseposition.y <= position.y + boxcollider->GetHeightSize() / 2) {
			checkMouseStat();
		}
		else {
			StateUpdate(ButtonState::BUTTONSTATE_NONE);
		}
	}
	else if (circleCollider != nullptr) {
		if (circleCollider->GetRad() >= position.Distance(mouseposition)) {
			checkMouseStat();
		}
		else {
			StateUpdate(ButtonState::BUTTONSTATE_NONE);
		}
	}
	else {
		Rect rect = spriterenderer->GetVisibleArea();
		Vec2F scale = Vec2F(1, 1);

		for (Object* iter = GetOwner(); iter->GetParent() != nullptr; iter = iter->GetParent()) {
			scale *= iter->GetComponent<Transform>()->GetScale();
		}

		if (-rect.right / INCH_PER_DISTANCE / 2 * scale.x + transform->GetWorldPos().x <= mouseposition.x &&
			mouseposition.x <= rect.right / INCH_PER_DISTANCE / 2 * scale.x + transform->GetWorldPos().x &&
			-rect.bottom / INCH_PER_DISTANCE / 2 * scale.y + transform->GetWorldPos().y <= mouseposition.y &&
			mouseposition.y <= rect.bottom / INCH_PER_DISTANCE / 2 * scale.y + transform->GetWorldPos().y) {
			checkMouseStat();
		}
		else {
			StateUpdate(ButtonState::BUTTONSTATE_NONE);
		}
	}

	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT && clickedOn) {
		StateUpdate(ButtonState::BUTTONSTATE_NONE);
		GetOwner()->OnClickExit();
		ApplyListener(GetOwner()->onClickExit);

		clickedOn = false;
	}
}

void Button::Render()
{
}

void Button::Render(ViewRenderData &)
{
}

Button* Button::SetButtonEffectType(ButtonEffectType effectType) {
	this->effectType = effectType;

	return this;
}

Button* Button::SetNormalTexture(const std::string& path) {
	normalTexture = RG2R_TextureM->Load(path);

	return this;
}

Button* Button::SetHoverTexture(const std::string& path) {
	hoverTexture = RG2R_TextureM->Load(path);

	return this;
}

Button* Button::SetPushedTexture(const std::string& path) {
	pushedTexture = RG2R_TextureM->Load(path);

	return this;
}

ButtonEffectType Button::GetButtonEffectType() {
	return effectType;
}

void Button::StateUpdate(ButtonState state) {
	switch (state)
	{
	case ButtonState::BUTTONSTATE_NONE:
		switch (effectType)
		{
		case ButtonEffectType::BUTTONEFFECTTYPE_IMAGECHANGE:
			spriterenderer->SetTexture(normalTexture);
			break;
		case ButtonEffectType::BUTTONEFFECTTYPE_SCALECHANGE:
			transform->SetScale(normalScale);
			break;
		case ButtonEffectType::BUTTONEFFECTTYPE_RUNLAMBDA:
			normalLambda();
			break;
		case ButtonEffectType::BUTTONEFFECTTYPE_NONE:
			break;
		default:
			break;
		}
		break;
	case ButtonState::BUTTONSTATE_PUSHED:
		switch (effectType)
		{
		case BUTTONEFFECTTYPE_IMAGECHANGE:
			spriterenderer->SetTexture(pushedTexture);
			break;
		case BUTTONEFFECTTYPE_SCALECHANGE:
			transform->SetScale(pushedScale);
			break;
		case BUTTONEFFECTTYPE_RUNLAMBDA:
			pushedlLambda();
			break;
		case BUTTONEFFECTTYPE_NONE:
			break;
		default:
			break;
		}
		break;
	case ButtonState::BUTTONSTATE_HOVER:
		switch (effectType)
		{
		case BUTTONEFFECTTYPE_IMAGECHANGE:
			spriterenderer->SetTexture(hoverTexture);
			break;
		case BUTTONEFFECTTYPE_SCALECHANGE:
			transform->SetScale(hoverScale);
			break;
		case BUTTONEFFECTTYPE_RUNLAMBDA:
			hoverLambda();
			break;
		case BUTTONEFFECTTYPE_NONE:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}