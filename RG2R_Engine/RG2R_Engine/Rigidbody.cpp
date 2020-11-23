#include "stdafx.h"
#include "Rigidbody.h"
#include "Engine.h"
#include "Transform.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "CollisionInfo.h"

Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update() {
	acceleration = acceleration - acceleration / calculation_speed;
	velocity = acceleration * RG2R_TimeM->GetDeltaTime();
	this->GetOwner()->GetComponent<Transform>()
		->SetPos(this->GetOwner()->GetComponent<Transform>()->GetPos() + velocity);

	std::vector<Object*> objList = GetOwner()->GetScene()->FindObjectsCondition([=](Object* obj) ->bool {
		return obj == GetOwner() ? false : obj->GetIsEnable() && obj->GetComponent<Rigidbody>();
	});

	auto ownerboxCollider = GetOwner()->GetComponent<BoxCollider>();
	auto ownercircleCollider = GetOwner()->GetComponent<CircleCollider>();
	auto ownertransform = GetOwner()->GetComponent<Transform>();

	for (auto iter : objList) {
		auto iterboxcollider = iter->GetComponent<BoxCollider>();
		auto itercirclecollider = iter->GetComponent<CircleCollider>();
		auto itertransform = iter->GetComponent<Transform>();

		if (iterboxcollider && ownerboxCollider) {
			bool is_crash = true;

			Vec2F distance = ownertransform->GetPos() - itertransform->GetPos();
			Vec2F vecs[] = {
				iterboxcollider->GetWidthSize() * Vec2F(cos(ToRadian(ownertransform->GetRot())), sin(ToRadian(ownertransform->GetRot()))) / 2,
				iterboxcollider->GetHeightSize() * Vec2F(cos(ToRadian(ownertransform->GetRot() - 90)), sin(ToRadian(ownertransform->GetRot() - 90))) / 2,
				ownerboxCollider->GetWidthSize() * Vec2F(cos(ToRadian(itertransform->GetRot())), sin(ToRadian(itertransform->GetRot()))) / 2,
				ownerboxCollider->GetHeightSize() * Vec2F(cos(ToRadian(itertransform->GetRot() - 90)), sin(ToRadian(itertransform->GetRot() - 90))) / 2
			};

			for (auto vec : vecs) {
				double sum = 0;
				auto unit = vec.Normalize();

				for (auto vec1 : vecs) {
					sum += Abs(vec1.Dot(unit));
				}

				if (Abs(distance.Dot(unit)) >= sum) {
					is_crash = false;
				}
			}

			CollisionInfo *collision = new CollisionInfo{ iter };

			if (is_crash) {
				if (!isFirstCollision.count(iter) || isFirstCollision[iter]) {
					ApplyListener(GetOwner()->onCollisionEnterListener, collision);
					GetOwner()->OnCollisionEnter(collision);
					isFirstCollision[iter] = false;
				}
				else {
					ApplyListener(GetOwner()->onCollisionStayListener, collision);
					GetOwner()->OnCollisionStay(collision);
				}
			}
			else if (isFirstCollision.count(iter) && !isFirstCollision[iter]) {
				ApplyListener(GetOwner()->onCollisionExitListener, collision);
				GetOwner()->OnCollisionExit(collision);
				isFirstCollision[iter] = true;
			}
		}
		else if (itercirclecollider && ownerboxCollider) {
			bool is_crash = true;

			Vec2F a1(cos(itertransform->GetRot()), sin(itertransform->GetRot()));
			Vec2F a2(-sin(itertransform->GetRot()), cos(itertransform->GetRot()));

			Vec2F l = ownertransform->GetPos() - itertransform->GetPos();

			if (itertransform->GetPos().x - ownerboxCollider->GetWidthSize() <= ownertransform->GetPos().x && ownertransform->GetPos().x <= itertransform->GetPos().x + ownerboxCollider->GetWidthSize() ||
				itertransform->GetPos().y - ownerboxCollider->GetHeightSize() <= ownertransform->GetPos().y && ownertransform->GetPos().y <= itertransform->GetPos().y + ownerboxCollider->GetHeightSize()) {

				if (ownerboxCollider->GetWidthSize() + itercirclecollider->GetRad() <= fabs(l.Dot(a1))) {
					is_crash = false;
				}

				if (ownerboxCollider->GetHeightSize() + itercirclecollider->GetRad() <= fabs(l.Dot(a2))) {
					is_crash = false;
				}
			}
			else {
				if (ownertransform->GetPos().x >= itertransform->GetPos().x) {
					if (ownertransform->GetPos().y >= itertransform->GetPos().y) {
						Vec2F point(itertransform->GetPos().x + ownerboxCollider->GetWidthSize(), itertransform->GetPos().y + ownerboxCollider->GetHeightSize());

						if (itercirclecollider->GetRad() < sqrt(pow(point.x - ownertransform->GetPos().x, 2) + pow(point.y - ownertransform->GetPos().y, 2))) {
							is_crash = false;
						}
					}
					else {
						Vec2F point(itertransform->GetPos().x + ownerboxCollider->GetWidthSize(), itertransform->GetPos().y - ownerboxCollider->GetHeightSize());

						if (itercirclecollider->GetRad() < sqrt(pow(point.x - ownertransform->GetPos().x, 2) + pow(point.y - ownertransform->GetPos().y, 2))) {
							is_crash = false;
						}
					}
				}
				else {
					if (ownertransform->GetPos().y >= itertransform->GetPos().y) {
						Vec2F point(itertransform->GetPos().x - ownerboxCollider->GetWidthSize(), itertransform->GetPos().y + ownerboxCollider->GetHeightSize());

						if (itercirclecollider->GetRad() < sqrt(pow(point.x - ownertransform->GetPos().x, 2) + pow(point.y - ownertransform->GetPos().y, 2))) {
							is_crash = false;
						}
					}
					else {
						Vec2F point(itertransform->GetPos().x - ownerboxCollider->GetWidthSize(), itertransform->GetPos().y - ownerboxCollider->GetHeightSize());

						if (itercirclecollider->GetRad() < sqrt(pow(point.x - ownertransform->GetPos().x, 2) + pow(point.y - ownertransform->GetPos().y, 2))) {
							is_crash = false;
						}
					}
				}
			}

			Vec2F crashline = ownertransform->GetPos() - itertransform->GetPos();

			if (abs(crashline.x) > abs(crashline.y)) {
				crashline = a1;
			}
			else {
				crashline = a2;
			}

			CollisionInfo *collision = new CollisionInfo{ iter , crashline };

			if (is_crash) {
				if (!isFirstCollision.count(iter) || isFirstCollision[iter]) {
					ApplyListener(GetOwner()->onCollisionEnterListener, collision);
					GetOwner()->OnCollisionEnter(collision);
					isFirstCollision[iter] = false;
				}
				else {
					ApplyListener(GetOwner()->onCollisionStayListener, collision);
					GetOwner()->OnCollisionStay(collision);
				}
			}
			else if (isFirstCollision.count(iter) && !isFirstCollision[iter]) {
				ApplyListener(GetOwner()->onCollisionExitListener, collision);
				GetOwner()->OnCollisionExit(collision);
				isFirstCollision[iter] = true;
			}
		}
		else if (itercirclecollider && ownercircleCollider) {
			Vec2F distance = ownertransform->GetPos() - itertransform->GetPos();

			Vec2F crashline = distance.Normalize();
			CollisionInfo *collision = new CollisionInfo{ iter , crashline };

			if (itercirclecollider->GetRad() + ownercircleCollider->GetRad() >= sqrt(pow(distance.x, 2) + pow(distance.y, 2))) {
				if (!isFirstCollision.count(iter) || isFirstCollision[iter]) {
					ApplyListener(GetOwner()->onCollisionEnterListener, collision);
					GetOwner()->OnCollisionEnter(collision);
					isFirstCollision[iter] = false;
				}
				else {
					ApplyListener(GetOwner()->onCollisionStayListener, collision);
					GetOwner()->OnCollisionStay(collision);
				}
			}
			else if (isFirstCollision.count(iter) && !isFirstCollision[iter]) {
				ApplyListener(GetOwner()->onCollisionExitListener, collision);
				GetOwner()->OnCollisionExit(collision);
				isFirstCollision[iter] = true;
			}
		}
	}
}

void Rigidbody::Render()
{
}

void Rigidbody::Render(ViewRenderData &)
{
}

Rigidbody* Rigidbody::SetForce(Vec2F _acceleration) {
	acceleration = _acceleration;

	return this;
}

Rigidbody* Rigidbody::SetForce(float _x, float _y) {
	acceleration = Vec2F(_x, _y);

	return this;
}

Rigidbody* Rigidbody::AddForce(Vec2F _acceleration) {
	acceleration += _acceleration;

	return this;
}

Rigidbody* Rigidbody::AddForce(float _x, float _y) {
	acceleration += Vec2F(_x, _y);

	return this;
}

Rigidbody* Rigidbody::SetCalculationSpeed(float _calculation_speed) {
	calculation_speed = _calculation_speed;

	return this;
}

Vec2F Rigidbody::GetForce() {
	return acceleration;
}

float Rigidbody::GetCalculationSpeed() {
	return calculation_speed;
}