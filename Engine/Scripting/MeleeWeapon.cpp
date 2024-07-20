#include "MeleeWeapon.h"
#include "TrailComponent.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ScriptComponent.h"
#include "GameManager.h"
#include "PlayerController.h"
#include "AnimationComponent.h"
#include "Hammer.h"
#include "Katana.h"

#include <algorithm>

MeleeWeapon::MeleeWeapon(BoxColliderComponent* collider, TrailComponent* trail) : Weapon()
{
    mType = WeaponType::MELEE;
    mCollider = collider;
    mTrail = trail;

    if (mCollider) 
    {
        mCollider->AddCollisionEventHandler(CollisionEventType::ON_COLLISION_ENTER,
            new std::function<void(CollisionData*)>(std::bind(&MeleeWeapon::OnCollisionEnter, this, std::placeholders::_1)));
    
    }
    mPlayerGO = GameManager::GetInstance()->GetPlayer();
    mPlayerController = GameManager::GetInstance()->GetPlayerController();
}

MeleeWeapon::~MeleeWeapon()
{
}

void MeleeWeapon::AttackEnter()
{ 
    if (mCollider) mCollider->GetOwner()->SetEnabled(true);
    if (mTrail) mTrail->SetEnable(true);

    //mPlayerController->SetSpineAnimation("tAttackMelee ", 0.9f);

    App->GetInput()->SetGameControllerRumble(0, 45000, 100);
}

void MeleeWeapon::AttackUpdate(float time)
{
   //if (mLastTimeClicked > mComboEndTime)
   //{
   //    LOG("Combo 0");
   //    mComboStep = 0;
   //}
   //
   //if (mLastTimeClicked > mComboNextTime)
   //{   
   //    if (App->GetInput()->GetMouseKey(MouseKey::BUTTON_LEFT) == KeyState::KEY_DOWN)
   //    {
   //        OnClick();
   //    }
   //}

    mLastTimeClicked += App->GetDt();
}

void MeleeWeapon::AttackExit()
{
    if (mCollider) mCollider->GetOwner()->SetEnabled(false);
    if (mTrail) mTrail->SetEnable(false);
}

void MeleeWeapon::OnClick()
{ 
    mLastTimeClicked = 0.0f;

    mComboStep++;
    if (mComboStep == 1)
    {
        LOG("Combo 1");
        mPlayerController->SetSpineAnimation("tAttackMelee", 0.9f);
    }

    mComboStep = std::clamp(mComboStep, 0, 3);

    if (mComboStep >= 2 && mPlayerController->GetAnimationComponent()->HasCurrentSpineStateFinished(1.0f))
    {
        LOG("Combo 2");
        mPlayerController->SetSpineAnimation("tAttackMelee", 0.9f);
    }

    if (mComboStep >= 3 && mPlayerController->GetAnimationComponent()->HasCurrentSpineStateFinished(1.0f))
    {
        LOG("Combo 3");
        mPlayerController->SetSpineAnimation("tAttackMelee", 0.9f);
    }
}

void MeleeWeapon::OnCollisionEnter(CollisionData* collisionData)
{
    if (collisionData->collidedWith->GetTag() == "Enemy")
    {
        Enemy* enemyScript = reinterpret_cast<Enemy*>(reinterpret_cast<ScriptComponent*>(collisionData->collidedWith->GetComponent(ComponentType::SCRIPT))->GetScriptInstance());
        if (enemyScript) enemyScript->TakeDamage(mDamage);

        HitEffect(collisionData);
        LOG("Colliding with enemy!");
    }
}