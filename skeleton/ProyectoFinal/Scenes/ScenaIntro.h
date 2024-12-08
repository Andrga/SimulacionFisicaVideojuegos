#pragma once
#include "../../basics/Scene.h"
class ScenaIntro : public Scene
{
public:
	ScenaIntro(PxPhysics* gphys, PxScene* gscn) :Scene(GetCamera(), gphys, gscn) {};
	~ScenaIntro() {}

	void setup()override;
};

