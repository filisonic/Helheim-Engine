#pragma once
#include "Weapon.h"

class GameObject;

class RangeWeapon : public Weapon
{

public:
	RangeWeapon();
	~RangeWeapon();

protected:
	GameObject* mFire = nullptr;
	virtual void PlayHitSound() = 0;
};

