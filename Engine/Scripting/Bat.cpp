#include "Bat.h"
#include "Application.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Enemy.h"
#include "ScriptComponent.h"

Bat::Bat(BoxColliderComponent* collider, TrailComponent* trail) : MeleeWeapon(collider, trail)
{
    mDamage = 4.0f;
    mAttackCooldown = 0.75;
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
    LOG("apply special effects bat");
}


