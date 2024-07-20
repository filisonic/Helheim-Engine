#pragma once
#include "Weapon.h"
#include "TimerScript.h"

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

	void OnClick();

	void OnCollisionEnter(CollisionData* collisionData);

protected:
	//Methods
	virtual void PlayHitSound() = 0;
	virtual void HitEffect(CollisionData* collisionData) = 0;

	//Common
	BoxColliderComponent* mCollider = nullptr;
	TrailComponent* mTrail = nullptr;

	TimerScript mTimeDelay;

	int mComboStep = 0;
	
	float mLastTimeClicked = 0.0f;

	float mComboEndTime = 5.0f;
	float mComboNextTime = 1.0f;

	GameObject* mPlayerGO = nullptr;
	PlayerController* mPlayerController = nullptr;
};

