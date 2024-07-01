#pragma once

class Weapon
{
public:
	enum class WeaponType {
		RANGE,
		MELEE,
		NONE
	};

	Weapon();
	~Weapon();

	virtual void AttackEnter() = 0;
	virtual void AttackUpdate(float time) = 0;
	virtual void AttackExit() = 0;

	WeaponType GetType() { return mType; }
	int GetCurrentAmmo() { return mCurrentAmmo; }
	int GetMaxAmmo() { return mMaxAmmo; }
	int GetDamage() { return mDamage; }

	float GetAttackDuration() { return mAttackDuration; }
	float GetAttackCooldown() { return mAttackCooldown; }
	
	void SetCurrentAmmo(int value) { mCurrentAmmo = value; }
	void SetDamage(int value) { mDamage = value; }
protected:
	virtual void PlayHitSound() = 0;
	WeaponType mType = WeaponType::NONE;

	float mDamage = 0.0f;
	float mAttackRange = 0.0f;

	float mAttackCooldown = 0.0f;
	float mAttackDuration = 0.0f;

	int mCurrentAmmo = 0;
	int mMaxAmmo = 0;
};

