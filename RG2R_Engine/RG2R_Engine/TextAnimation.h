#pragma once
#include "Component.h"

#include <vector>

class TextRenderer;

class TextAnimation :
	public Component
{
private:
	TextRenderer* textRenderer;

	std::string targetText;
	std::string nowText;

	float delay = 0;
	float currentDelay = 0;

	float interval = 0.05f;
	float currentinterval = 0.05f;
public:
	TextAnimation();
	~TextAnimation();

	std::type_index GetID(void) override { return typeid(TextAnimation); }
	static std::type_index GetFamilyID(void) { return typeid(TextAnimation); }

	void Render() {}
	void Render(ViewRenderData&) {}

	void Update();
	void OnStart();

	TextAnimation* SetTargetText(const std::string&);
	TextAnimation* SetInterval(float);
	TextAnimation* SetDelay(float);
	TextAnimation* Reset();

	std::string GetTargetText();
	float GetInterval();
};

//우는 우동 짬 ㅎㅎ 나는