#pragma once
#include "Object.h"
#include "../RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"

class Widget : public Object
{
public:
	Widget(Vector3 Pos = { 0,0,0 }, float siz = 1);
	Widget(Vector3 Pos = { 0,0,0 }, physx::PxShape* shap = nullptr);
	~Widget() {};

	void changeShape(physx::PxShape* shap);

	bool update(double t) override { return true; };
	void setVisibility(bool visibility) override;

private:
	Vector3 position = { 0,0,0 };
	float size = 1;
	RenderItem* renderItem = nullptr;
	physx::PxTransform* pose;
};

