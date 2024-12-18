#pragma once
#include "../scenes/SceneParticleSystem.h"
#include "../scenes/SceneNiebla.h"

#include "../scenes/ScenaViento.h"
#include "../scenes/ScenaTorbellino.h"
#include "../scenes/ScenaExplosion.h"
#include "../scenes/ScenaMuelles.h"

#include "../scenes/ScenaSolidoRigido.h"

#include <vector>
using namespace std;

class SceneManager
{
private:
	vector<Scene*> scenes;
	PxPhysics* gPhysics;
	PxScene* gScene;
	int actualScene = 0;
public:
	SceneManager(PxPhysics* gphys, PxScene* gscn);
	~SceneManager();
	
	void addScene(Scene* scn);
	void update(float t);

	void setScene(int id);

	void keyPressed(unsigned char key, const physx::PxTransform& camera);

};

