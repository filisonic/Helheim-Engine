#pragma once
#include "RangeWeapon.h"

class Machinegun : public RangeWeapon
{
public:
	Machinegun();
	~Machinegun();

	void AttackEnter() override;
	void AttackUpdate(float time) override;
	void AttackExit() override;

private:
	void PlayHitSound();
	bool Delay(float delay);

	unsigned int mNumBullets = 3;
	float mShootDuration;
	bool mFirstShoot = true;
	float mTimePassed = 0.0f;
};
