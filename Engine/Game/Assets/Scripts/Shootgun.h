#pragma once
#include "RangeWeapon.h"

class Shootgun : public RangeWeapon
{
public:
	Shootgun();
	~Shootgun() {}
	void AttackEnter() override;
	void AttackUpdate(float time) override;

private:
	void PlayHitSound();
};
