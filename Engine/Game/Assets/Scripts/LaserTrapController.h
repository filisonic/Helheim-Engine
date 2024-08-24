#pragma once
#include <Script.h>
#include <vector>
#include "Macros.h"
#include "TimerScript.h"

struct CollisionData;
class BoxColliderComponent;
class GameObject;

GENERATE_BODY(LaserTrapController);
class LaserTrapController :
	public Script
{
	FRIEND(LaserTrapController)
public:
	LaserTrapController(GameObject* owner);
	~LaserTrapController();
	void Update() override;
	void Start() override;
	void OnCollisionEnter(CollisionData* collisionData);

private:
	bool CheckIfCaptured(const GameObject* target);
	void ActiveTrap(bool active);

	BoxColliderComponent* mCollider = nullptr;
	std::vector<GameObject*> mInTrap;

	float mArea = 1.0f;
	GameObject* mSfx = nullptr;

	// Activation
	bool mIsActive = false;
	float mActivationInterval = 8.0f;
	float mActivationDuration = 4.0f;
	TimerScript mActivationIntervalTimer;
	TimerScript mActivationDurationTimer;

	// Damage
	float mDamageAmount = 5.0f;
	float mSpeedReduction = 0.3f; // Reduce 70%
};

