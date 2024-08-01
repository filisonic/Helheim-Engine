#include "Hammer.h"
#include "Application.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Enemy.h"
#include "ScriptComponent.h"

Hammer::Hammer(BoxColliderComponent* collider, TrailComponent* trail) : MeleeWeapon(collider, trail)
{
    mDamage = 6.0f;
    mAttackDuration = 0.7f;
    mAttackCooldown = 1.0f;
}

Hammer::~Hammer()
{
}

void Hammer::PlayHitSound()
{
    GameManager::GetInstance()->GetAudio()->PlayOneShot(SFX::MEELEE,
        GameManager::GetInstance()->GetPlayer()->GetWorldPosition(),
        { { "Speed", 8.0f } }
    );
}

void Hammer::HitEffect(CollisionData* collisionData)
{
    Enemy* enemyScript = static_cast<Enemy*>(static_cast<ScriptComponent*>(collisionData->collidedWith->GetComponent(ComponentType::SCRIPT))->GetScriptInstance());
    if (enemyScript)
    {
        enemyScript->TakeDamage(mDamage);
    }
}

