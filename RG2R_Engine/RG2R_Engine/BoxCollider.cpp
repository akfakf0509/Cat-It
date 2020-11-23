#include "stdafx.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Renderer.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(float _width, float _height) {
	area = { _width, _height };
}


BoxCollider::~BoxCollider()
{
}

Vec2F BoxCollider::GetArea() {
	return area;
}

float BoxCollider::GetWidthSize() {
	return area.x;
}

float BoxCollider::GetHeightSize() {
	return area.y;
}

BoxCollider* BoxCollider::SetArea(Vec2F area) {
	this->area = area;

	return this;
}

BoxCollider* BoxCollider::SetArea(float width, float height) {
	this->area = { width, height };

	return this;
}

BoxCollider* BoxCollider::SetAreaAuto() {
	Renderer* renderer = GetOwner()->GetComponent<Renderer>();

	if (renderer != nullptr) {
		area = { area.x == -1 ? renderer->GetVisibleArea().right / INCH_PER_DISTANCE : area.x,  area.y == -1 ? renderer->GetVisibleArea().bottom / INCH_PER_DISTANCE : area.y };
	}
	else {
		std::cout << "Renderer is undefined" << std::endl;
	}

	return this;
}

BoxCollider* BoxCollider::SetWidthSize(float _width) {
	area.x = _width;

	return this;
}

BoxCollider* BoxCollider::SetHeightSize(float _height) {
	area.y = _height;

	return this;
}