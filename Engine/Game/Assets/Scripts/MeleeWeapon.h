#pragma once
#include "Weapon.h"

class TrailComponent;
class BoxColliderComponent;
class GameObject;
class PlayerController;
struct CollisionData;

class MeleeWeapon : public Weapon
{
public:
	MeleeWeapon(BoxColliderComponent* collider, TrailComponent* trail);
	~MeleeWeapon();

	void AttackEnter() override;
	void AttackUpdate(float time) override;
	void AttackExit() override;

	void OnCollisionEnter(CollisionData* collisionData);

protected:
	//Methods 
	virtual void HitEffect(CollisionData* enemy) = 0;

	//Common
	BoxColliderComponent* mCollider = nullptr;
	TrailComponent* mTrail = nullptr;

	GameObject* mPlayerGO = nullptr;
	PlayerController* mPlayerController = nullptr;

	//Specific 
	float mRange = 1.0f;
	float mDamage = 1;
	int mEnergyCost = 0;
};

