#include "stdafx.h"
#include "TextAnimation.h"

#include "TextRenderer.h"
#include "Engine.h"

TextAnimation::TextAnimation() {}

TextAnimation::~TextAnimation() {}

void TextAnimation::OnStart() {
	textRenderer = GetOwner()->GetComponent<TextRenderer>();

	if (textRenderer == nullptr) {
		std::cout << "TextRenderer is nullptr" << std::endl;

		SetIsEnable(false);
	}
	
	currentDelay = delay;
}

void TextAnimation::Update() {
	if (currentDelay <= 0) {
		currentinterval -= RG2R_TimeM->GetDeltaTime();	

		if (currentinterval <= 0) {
			currentinterval = interval;

			if (nowText != targetText) {
				std::string tmp = targetText;

				if ((tmp[nowText.size()] & 0x80) != 0x80) {
					tmp.resize(nowText.size() + 1);
				}
				else {
					tmp.resize(nowText.size() + 2);
				}

				nowText = tmp;

				textRenderer->SetText(tmp);
			}
		}
	}
	else {
		currentDelay -= RG2R_TimeM->GetDeltaTime();
	}
}

TextAnimation* TextAnimation::SetTargetText(const std::string& text) {
	targetText = text;

	return this;
}

TextAnimation* TextAnimation::SetInterval(float interval) {
	this->interval = interval;
	this->currentinterval = interval;

	return this;
}

TextAnimation* TextAnimation::SetDelay(float delay) {
	this->delay = delay;

	return this;
}

TextAnimation* TextAnimation::Reset() {
	textRenderer->SetText("");
	nowText = "";
	currentDelay = delay;

	return this;
}

std::string TextAnimation::GetTargetText() {
	return targetText;
}

float TextAnimation::GetInterval() {
	return interval;
}