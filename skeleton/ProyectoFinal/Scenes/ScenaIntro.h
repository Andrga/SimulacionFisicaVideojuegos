#pragma once
#include "../../basics/Scene.h"
#include "../Basics/Button.h"
#include "../../basics/RBDynamic.h"
class ScenaIntro : public Scene
{
public:
	ScenaIntro(SceneManager* scnMang, PxPhysics* gphys, PxScene* gscn) :Scene(scnMang, gphys, gscn) {};
	~ScenaIntro() {}

	void setup()override;

	// metodos de los botones
	void Start();
	void Quit();

};

