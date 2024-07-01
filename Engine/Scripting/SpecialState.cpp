#include "SpecialState.h"
#include "Application.h"
#include "PlayerController.h"
#include "Weapon.h"

#include "Application.h"
#include "PlayerController.h"

SpecialState::SpecialState(PlayerController* player, float cooldown) : State(player, cooldown)
{
}

SpecialState::~SpecialState()
{
}

StateType SpecialState::HandleInput()
{
    if (mPlayerController->GetPlayerLowerState()->GetType() == StateType::DASH) return StateType::AIM;

    mSpecialAttackTimer += App->GetDt();
    if (mSpecialAttackTimer < mSpecialWeapon->GetAttackDuration())
    {
        return StateType::SPECIAL;
    }

    return StateType::AIM;
}

void SpecialState::Update()
{
	mSpecialWeapon->AttackUpdate(mSpecialAttackTimer);
}

void SpecialState::Enter()
{
	mSpecialAttackTimer = 0.0f;
	mSpecialWeapon = mPlayerController->GetSpecialWeapon();
	if (mSpecialWeapon)
	{
		mPlayerController->SetSpineAnimation("tSpecial", 0.1f);
		mSpecialWeapon->AttackEnter();
	}
}

void SpecialState::Exit()
{
	mSpecialWeapon->AttackExit();
	mSpecialWeapon = nullptr;
}

StateType SpecialState::GetType()
{
	return StateType::SPECIAL;
}

bool SpecialState::IsReady()
{
	mStateTimer += App->GetDt();
	if (mStateTimer >= mStateCooldown && mPlayerController->GetEnergyType() != EnergyType::NONE) return true;
	return false;
}
