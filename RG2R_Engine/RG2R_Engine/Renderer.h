#pragma once
#include "Component.h"
#include "ViewRenderData.h"

class Component;
class ViewRenderData;

class Renderer :
	public Component
{
private:
	float z_index = 0;

public:
	Renderer();
	~Renderer();

	virtual std::type_index GetID(void) override = 0 { return typeid(Renderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Render(ViewRenderData&) = 0;
	virtual void Draw() = 0;
	virtual void Draw(ViewRenderData&) = 0;

	virtual Rect GetVisibleArea() { return Rect(); };
	virtual Rect GetRealArea() { return Rect(); };

	void SetZ_index(float);
	float GetZ_index();
};