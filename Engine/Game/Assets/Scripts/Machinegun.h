#pragma once
#include "RangeWeapon.h"
#include "TimerScript.h"
class Machinegun : public RangeWeapon
{
public:
	Machinegun();
	~Machinegun() {}

	void AttackEnter() override;
	void AttackUpdate(float time) override;
	void AttackExit() override;
private:
	void PlayHitSound();

	unsigned int mNumBullets;
	float mShootDuration;
	bool mFirstShoot = true;
	float mTimePassed = 0.0f;

	TimerScript mShootTimer;

};
