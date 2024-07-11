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
#include "Hammer.h"
#include "Katana.h"

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
    mComboEndTimer += App->GetDt();
    if (mComboEndTimer >= mComboEndDuration)
    {
        mComboStep = 0;
    }
    else
    {
        mComboStep++;
    }

    switch (mComboStep)
    {
        case 0:
            mDamage = 1.0f;
            // Size of collider and other combo step related changes
            mPlayerController->SetSpineAnimation("tAttackMelee", 0.9f);
            break;
        case 1:
            mDamage = 1.5f;
            // Size of collider and other combo step related changes
            mPlayerController->SetSpineAnimation("tAttackMelee", 0.9f);
            break;
        case 2:
            mDamage = 2.0f;
            // Size of collider and other combo step related changes
            mPlayerController->SetSpineAnimation("tAttackMelee", 0.9f);
            break;
    }

    if (mCollider) mCollider->GetOwner()->SetEnabled(true);
    if (mTrail) mTrail->SetEnable(true);

    App->GetInput()->SetGameControllerRumble(0, 45000, 100);
}

void MeleeWeapon::AttackUpdate(float time)
{
}

void MeleeWeapon::AttackExit()
{
    if (mCollider) mCollider->GetOwner()->SetEnabled(false);
    if (mTrail) mTrail->SetEnable(false);
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