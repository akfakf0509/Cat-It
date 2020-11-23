#pragma once
#include "Collider.h"
class BoxCollider :
	public Collider
{
private:
	Vec2F area = { 0, 0 };

public:
	BoxCollider();
	BoxCollider(float, float);
	~BoxCollider();

	void Update() {};
	void Render() {};
	void Render(ViewRenderData&) {};

	std::type_index GetID() { return typeid(BoxCollider); }
	static std::type_index GetFamilyID(void) { return typeid(BoxCollider); }

	Vec2F GetArea();
	float GetWidthSize();
	float GetHeightSize();

	BoxCollider* SetArea(Vec2F);
	BoxCollider* SetArea(float, float);
	BoxCollider* SetAreaAuto();
	BoxCollider* SetWidthSize(float);
	BoxCollider* SetHeightSize(float);
};

