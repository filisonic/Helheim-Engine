
#include "LaserTrapController.h"
#include "GameManager.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "ScriptComponent.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "Application.h"
#include "ModuleScene.h"

CREATE(LaserTrapController)
{
    CLASS(owner);
    SEPARATOR("ACTIVATION PARAMETER");
    MEMBER(MemberType::FLOAT, mActivationInterval);
    MEMBER(MemberType::FLOAT, mActivationDuration);
    MEMBER(MemberType::BOOL, mIsActive);

    SEPARATOR("SIDE EFFECT");
    MEMBER(MemberType::FLOAT, mDamageAmount);
    MEMBER(MemberType::FLOAT, mSpeedReduction);
    END_CREATE;
}

LaserTrapController::LaserTrapController(GameObject* owner) : Script(owner)
{
}

LaserTrapController::~LaserTrapController()
{
    mInTrap.clear();
}

void LaserTrapController::Start()
{
    mSfx = App->GetScene()->InstantiatePrefab("TrapSFX.prfb");
    if (mSfx)
    {
        mSfx->SetParent(mGameObject);
        mSfx->SetEnabled(mIsActive);
    }

    mCollider = static_cast<BoxColliderComponent*>(mGameObject->GetComponent(ComponentType::BOXCOLLIDER));
    if (mCollider)
    {
        mCollider->AddCollisionEventHandler(CollisionEventType::ON_COLLISION_ENTER, new std::function<void(CollisionData*)>(std::bind(&LaserTrapController::OnCollisionEnter, this, std::placeholders::_1)));
    }
}

void LaserTrapController::Update()
{
    if (mIsActive)
    {
        if (mActivationDurationTimer.Delay(mActivationDuration))
        {
            mIsActive = false;
            ActiveTrap(false);
        }
    }
    else
    {
        if (mActivationIntervalTimer.Delay(mActivationInterval))
        {
            mIsActive = true;
            ActiveTrap(true);
        }
    }
}



bool LaserTrapController::CheckIfCaptured(const GameObject* target)
{
    for (auto captured : mInTrap)
    {
        if (captured->GetID() == target->GetID())
        {
            return true;
        }
    }
    return false;
}

void LaserTrapController::ActiveTrap(bool active)
{
    if (active)
    {
        LOG("Trap active");
        if (mSfx)
        {
            mSfx->SetEnabled(true);
        }
        // Reserved for effects, perticle, sounds...
    }
    else
    {
        mInTrap.clear();
        LOG("Trap not active");
        if (mSfx)
        {
            mSfx->SetEnabled(false);
        }
        // Reserved for effects, perticle, sounds...
    }
}

void LaserTrapController::OnCollisionEnter(CollisionData* collisionData)
{
    GameObject* collision = collisionData->collidedWith;

    if (!CheckIfCaptured(collision) && mIsActive)
    {
        mInTrap.push_back(collision);

        if (collision->GetTag().compare("Player") == 0)
        {
            const ScriptComponent* script = static_cast<ScriptComponent*>(collision->GetComponent(ComponentType::SCRIPT));
            PlayerController* player = static_cast<PlayerController*>(script->GetScriptInstance());
            player->Paralyzed(mSpeedReduction, true);
            player->TakeDamage(mDamageAmount);
        }

        if (collision->GetTag().compare("Enemy") == 0)
        {
            const ScriptComponent* script = static_cast<ScriptComponent*>(collision->GetComponent(ComponentType::SCRIPT));
            Enemy* enemy = static_cast<Enemy*>(script->GetScriptInstance());
            enemy->Paralyzed(mSpeedReduction, true);
            enemy->TakeDamage(mDamageAmount);
        }
    }
}
