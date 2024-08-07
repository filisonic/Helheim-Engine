#pragma once
#include "Script.h"
#include "Macros.h"

GENERATE_BODY(LoreCollectible);

class GameObject;
class BoxColliderComponent;
class CollisionData;
class TextComponent;
class ImageComponent;

class LoreCollectible : public Script
{
	FRIEND(LoreCollectible)

public:
    LoreCollectible(GameObject* owner);
    ~LoreCollectible() {}

    void Init();
    void Start() override;
    void Update() override;
    void OnCollisionEnter(CollisionData* collisionData);

private:

    BoxColliderComponent* mCollider = nullptr;
    GameObject* mCanvasGO = nullptr;
    TextComponent* mLoreText = nullptr;
    ImageComponent* mImage = nullptr;

};

