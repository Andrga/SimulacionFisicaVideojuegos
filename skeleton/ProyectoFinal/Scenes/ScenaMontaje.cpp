#include "ScenaMontaje.h"
#include "../../basics/SceneManager.h"
#include <algorithm>

void ScenaMontaje::setup()
{
	// coloca la camara
	camera->moveTo({ 0,0,-100 });

	// boton de confirmar cohete
	Button* but = new Button("Confirmar", this, gPhysics, gScene);
	but->setPosition({ 50,50,0 });
	but->setShape(CreateShape(PxBoxGeometry(10, 5, 1)), { 10, 5, 1 });
	addGameObject(but);
	gScene->addActor(*but->getActor());
	but->addCallback([this]() {this->saveRocket(); });
	but->addCallback([this]() {this->LaunchScene(); });

	cabina = new ObjetoMovible("mov1", this, gPhysics, gScene, CABINA);
	cabina->setPosition({ -20,20,0 });

	addGameObject(cabina);

	ObjetoMovible* movible2 = new ObjetoMovible("mov2", this, gPhysics, gScene, TANQUE);
	movible2->setPosition({ 0,20,0 });

	addGameObject(movible2);

	ObjetoMovible* movible4 = new ObjetoMovible("mov4", this, gPhysics, gScene, TANQUE);
	movible2->setPosition({ 0, 40,0 });

	addGameObject(movible4);

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
	sceneManager->setScene(2);
}
