#include "Katana.h"
#include "Application.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Enemy.h"
#include "ScriptComponent.h"

Katana::Katana(BoxColliderComponent* collider, TrailComponent* trail) : MeleeWeapon(collider, trail)
{
    mDamage = 2.0f;
    mAttackCooldown = 0.5f;
}

Katana::~Katana()
{
}

void Katana::PlayHitSound()
{
    GameManager::GetInstance()->GetAudio()->PlayOneShot( SFX::MEELEE,
        GameManager::GetInstance()->GetPlayer()->GetWorldPosition(),
        { { "Speed", 8.0f } }
    );
}

void Katana::HitEffect(CollisionData* collisionData)
{
    Enemy* enemyScript = reinterpret_cast<Enemy*>(reinterpret_cast<ScriptComponent*>(collisionData->collidedWith->GetComponent(ComponentType::SCRIPT))->GetScriptInstance());
    if (enemyScript)
    {
        enemyScript->PushBack();
    }
}
