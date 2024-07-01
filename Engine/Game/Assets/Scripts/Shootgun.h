#pragma once
#include "RangeWeapon.h"

class Shootgun : public RangeWeapon
{
public:
	Shootgun();
	~Shootgun();
	void AttackEnter() override;
	void AttackUpdate(float time) override;
	void AttackExit() override;

private:
	void PlayHitSound();

	unsigned int numBullets = 10;
};
