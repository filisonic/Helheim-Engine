#include "Bat.h"
#include "Application.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Enemy.h"
#include "ScriptComponent.h"

#include "GameManager.h"
#include "PlayerController.h"

Bat::Bat(BoxColliderComponent* collider, TrailComponent* trail) : MeleeWeapon(collider, trail)
{
    mDamage = 4.0f;
    mAttackDuration = 0.7f;
    mAttackCooldown = 0.5f;
}

Bat::~Bat()
{
}

void Bat::PlayHitSound()
{
    GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MEELEE,
        GameManager::GetInstance()->GetPlayer()->GetWorldPosition(),
        { { "Speed", 8.0f } }
    );
}

void Bat::HitEffect(CollisionData* collisionData)
{
    Enemy* enemyScript = static_cast<Enemy*>(static_cast<ScriptComponent*>(collisionData->collidedWith->GetComponent(ComponentType::SCRIPT))->GetScriptInstance());
    if (enemyScript)
    {
        enemyScript->TakeDamage(mDamage);
    }
    LOG("apply special effects bat");
}


