#pragma once
#include "Object.h"

#include <vector>

class Texture;

class ParticleSystem :
	public Object
{
private:
	Texture* texture;

	float summon = 0;

private:
	std::vector<std::string> particlePaths;
	std::vector<Object*> particles;

public:
	float summon1 = 1.f, summon2 = 2.f;
	float speed1 = 1.f, speed2 = 2.f;

	Vec2F moveVec = Vec2F(0, 0);

	Vec2F summonLine = Vec2F(0, 0);

	std::function<bool(Object*)> deleteLambda = [](Object* obj) { return false; };
public:
	ParticleSystem();
	~ParticleSystem();

	void OnUpdate();

	ParticleSystem* PushParticlePath(const std::string& path);
	ParticleSystem* SetTexture(const std::string& path);
	ParticleSystem* SetTexture(Texture*);

	Texture* GetTexture();
};

