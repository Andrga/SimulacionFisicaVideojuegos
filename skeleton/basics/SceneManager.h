#pragma once
#include "../scenes/SceneParticleSystem.h"
#include "../scenes/SceneNiebla.h"

#include "../scenes/ScenaViento.h"
#include "../scenes/ScenaTorbellino.h"
#include "../scenes/ScenaExplosion.h"
#include "../scenes/ScenaMuelles.h"

#include "../scenes/ScenaSolidoRigido.h"
#include "../ProyectoFinal/scenes/ScenaIntro.h"
#include "../ProyectoFinal/scenes/ScenaMontaje.h"
#include "../ProyectoFinal/scenes/ScenaLaunch.h"

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
	void keyReleased(unsigned char key, const physx::PxTransform& camera);
	void mouseInput(int button, int state, int x, int y);

};

