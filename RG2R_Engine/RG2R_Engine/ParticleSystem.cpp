#include "stdafx.h"
#include "ParticleSystem.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Texture.h"
#include "Engine.h"

#include "RandomGenerator.h"

ParticleSystem::ParticleSystem() {
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::OnUpdate() {
	summon -= RG2R_TimeM->GetDeltaTime();

	if (summon <= 0) {
		RandomGenerator* randomGenerator = new RandomGenerator();
		int index = randomGenerator->GetInt(0, particlePaths.size() - 1);

		Object* tmp = CreateChildObject();
		tmp->AttachComponent<SpriteRenderer>()
			->SetTexture(particlePaths[index]);
		tmp->GetComponent<Transform>()
			->SetAnchor(tmp->GetComponent<SpriteRenderer>()->GetVisibleArea().GetCenter())
			->SetPos(randomGenerator->GetFloat(-summonLine.x / 2, summonLine.x / 2), randomGenerator->GetFloat(-summonLine.y / 2, summonLine.y / 2));

		tmp->onUpdateListener = [=]() {
			tmp->GetComponent<Transform>()
				->Translate(moveVec * randomGenerator->GetFloat(speed1, speed2) * RG2R_TimeM->GetDeltaTime());
		};

		particles.push_back(tmp);

		summon = randomGenerator->GetFloat(summon1, summon2);
	}

	for (auto iter = particles.begin(); iter < particles.end();) {
		if (deleteLambda(*iter)) {
			(*iter)->Destroy();
			iter = particles.erase(iter);
		}
		else {
			iter++;
		}
	}
}

ParticleSystem* ParticleSystem::PushParticlePath(const std::string& path) {
	particlePaths.push_back(path);

	return this;
}

ParticleSystem* ParticleSystem::SetTexture(const std::string& path) {
	texture = RG2R_TextureM->Load(path);

	return this;
}

ParticleSystem* ParticleSystem::SetTexture(Texture* texture) {
	this->texture = texture;

	return this;
}

Texture* ParticleSystem::GetTexture() {
	return texture;
}