#pragma once
#include "RangeWeapon.h"

class Pistol : public RangeWeapon
{
public:
	Pistol();
	~Pistol() {}

	void AttackEnter() override;
	void AttackUpdate(float time) override;
	void Reload();

private:
	void PlayHitSound();

};

