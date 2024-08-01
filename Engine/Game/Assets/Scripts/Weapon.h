	#pragma once

class Weapon
{
public:
	enum class WeaponType 
	{
		RANGE,
		MELEE,
		NONE
	};

	Weapon();
	~Weapon();

	virtual void AttackEnter() {}
	virtual void AttackUpdate(float time) = 0;
	virtual void AttackExit() {}

	WeaponType GetType() { return mType; }

	float GetDamage() { return mDamage; }
	float GetAttackDuration() { return mAttackDuration; }
	float GetAttackCooldown() { return mAttackCooldown; }
	
	void SetDamage(float value) { mDamage = value; }
protected:
	virtual void PlayHitSound() = 0;
	WeaponType mType = WeaponType::NONE;

	float mDamage = 0.0f;
	float mAttackRange = 0.0f;

	float mAttackCooldown = 0.0f;
	float mAttackDuration = 0.0f;
};

