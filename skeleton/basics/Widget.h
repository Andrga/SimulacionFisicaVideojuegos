#pragma once
#include "GameObject.h"
#include "../RenderUtils.hpp"

class Widget : public GameObject
{
public:
	Widget(string nam, Scene* scn, Vector3 Pos = { 0,0,0 }, float siz = 1);
	Widget(string nam, Scene* scn, Vector3 Pos = { 0,0,0 }, physx::PxShape* shap = nullptr);
	~Widget() {};

	void changeShape(physx::PxShape* shap);

	bool update(double t) override { return true; };
	void setVisibility(bool visibility) override;

private:
};

