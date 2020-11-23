#include "stdafx.h"
#include "ButtonObject.h"

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"

ButtonObject::ButtonObject() {
	AttachComponent<Button>();

	text = CreateChildObject();
	text->AttachComponent<TextRenderer>()
		->SetText("Button");
}

ButtonObject::~ButtonObject() {
}

void ButtonObject::OnUpdate()
{
	clickedOn = GetComponent<Button>()->clickedOn;
}
