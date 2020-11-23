#pragma once
#include "Component.h"

#include "ButtonEffectType.h"
#include "ButtonState.h"

class Texture;
class Transform;
class SpriteRenderer;
class BoxCollider;
class CircleCollider;

class Button :
	public Component
{
private:
	ButtonEffectType effectType = ButtonEffectType::BUTTONEFFECTTYPE_NONE;
	ButtonState state = ButtonState::BUTTONSTATE_NONE;

	Transform* transform;
	SpriteRenderer* spriterenderer;
	BoxCollider* boxcollider;
	CircleCollider* circleCollider;

public:
	bool clickedOn = false;

	Texture* normalTexture = nullptr;
	Texture* hoverTexture = nullptr;
	Texture* pushedTexture = nullptr;

	Vec2F normalScale = Vec2F(1, 1);
	Vec2F hoverScale = Vec2F(1.1f, 1.1f);
	Vec2F pushedScale = Vec2F(1.05f, 1.05f);

	std::function<void()> normalLambda = []() {};
	std::function<void()> hoverLambda = []() {};
	std::function<void()> pushedlLambda = []() {};

private:
	void StateUpdate(ButtonState);

public:
	Button();
	~Button();

	void Update() {}
	std::type_index GetID(void) override { return typeid(Button); }
	static std::type_index GetFamilyID(void) { return typeid(Button); }

	void OnStart();
	void OnUpdate();
	void Render();
	void Render(ViewRenderData&);

	Button* SetButtonEffectType(ButtonEffectType);

	Button* SetNormalTexture(const std::string&);
	Button* SetHoverTexture(const std::string&);
	Button* SetPushedTexture(const std::string&);

	ButtonEffectType GetButtonEffectType();
};