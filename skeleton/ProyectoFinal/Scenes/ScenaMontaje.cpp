#include "ScenaMontaje.h"
#include <algorithm>

void ScenaMontaje::setup()
{
	GameObject* butConfirm = new Button("buttonConfirmar", this, gPhysics, gScene);
	butConfirm->setShape(CreateShape(PxBoxGeometry(5, 5, 1)), { 5, 5, 1 });
	butConfirm->setPosition({ 50,50,0 });
	butConfirm->setColor({ 0.5,1,0.5,1 });
	butConfirm->addCallback([this]() {this->saveRocket(); });
	butConfirm->addCallback([this]() {this->LaunchScene(); });
	addGameObject(butConfirm);

	cabina = new ObjetoMovible("mov1", this, gPhysics, gScene, CABINA);
	cabina->setPosition({ -20,20,0 });

	addGameObject(cabina);

	ObjetoMovible* movible2 = new ObjetoMovible("mov2", this, gPhysics, gScene, TANQUE);
	movible2->setPosition({ 0,20,0 });

	addGameObject(movible2);

	ObjetoMovible* movible3 = new ObjetoMovible("mov3", this, gPhysics, gScene, PROPULSOR);
	movible3->setPosition({ 20,20,0 });

	addGameObject(movible3);
}

void ScenaMontaje::show()
{
	Scene::show();
	camera->moveTo(CAMERA_START_POS);
}

void ScenaMontaje::saveRocket()
{
	Cohete = cabina->generateModulo();
}

void ScenaMontaje::LaunchScene()
{
	cout << "LAUNCHSCENE" << endl;
}
