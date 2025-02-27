#ifndef _COMPONENT_SPOTLIGHT_H_
#define _COMPONENT_SPOTLIGHT_H_
#include "Component.h"
#include "Geometry/Frustum.h"

typedef struct SpotLight {

	float pos[4]; //w intensity
	float aimD[4];//w cos inner angle
	float color[4];//w cos outer angle
	float range;
	int shadowIndex;
	float padding[2];
	
}SpotLight;

class ENGINE_API SpotLightComponent : public Component
{
public:
	explicit SpotLightComponent(GameObject* owner);
	SpotLightComponent(const SpotLightComponent& original) = delete;
	~SpotLightComponent();

	SpotLightComponent& operator=(const SpotLightComponent& other) = delete;

	void Update() override;
	Component* Clone(GameObject* owner) const override;

	void Save(JsonObject& obj) const override;
	void Load(const JsonObject& data, const std::unordered_map<unsigned int, GameObject*>& uidPointerMap) override;

	void Reset() override;
	void Enable() override;
	void Disable() override;

	const SpotLight& GetData() const { return mData; }
	const float* GetPosition() const;
	const float* GetDirection() const { return mData.aimD; };
	const float* GetColor() const { return mData.color; }
	void SetColor(float col[3]);
	float GetIntensity() const { return mData.pos[3]; }
	void SetIntensity(float intensity);
	float GetRange() const { return mData.range; }
	void SetRange(float range);
	float GetOuterAngle() const;
	void SetOuterAngle(float angle);
	float GetInnerAngle() const;
	void SetInnerAngle(float angle);
	bool CanCastShadow() const { return mCastShadow; }
	void SetCastShadow(bool castShadow) { mCastShadow = castShadow; }
	float GetBias() const { return mBias; }
	void SetBias(float bias);
	int GetIndex() const { return mData.shadowIndex; }
	void SetShadowIndex(int index);

	const Frustum& GetFrustum() const { return mShadowFrustum; }

	void GetBoundingSphere(float boundingSphere[4]) const;

private:
	SpotLightComponent(const SpotLightComponent* original, GameObject* owner);
	SpotLight mData;
	Frustum mShadowFrustum;

	bool mCastShadow = false;
	float mBias;
};

#endif //_COMPONENT_SPOTLIGHT_H_