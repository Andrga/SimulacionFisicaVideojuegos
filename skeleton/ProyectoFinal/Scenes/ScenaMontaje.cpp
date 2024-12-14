#include "ScenaMontaje.h"
#include "../../basics/SceneManager.h"
#include <algorithm>

void ScenaMontaje::update(double t)
{
	Scene::update(t);

	// texto con informacion
	display_text_color = { 0,1,1,1 };
	display_text1_position = { 10,500 };
	display_text1 = "MONTAJE DE COHETE";
	display_text1 += "#------------------";
	display_text2_position = { 10,100 };
	display_text2 = "#CONTROLES";
	display_text2 += "#------------------";
	display_text2 += "#W,A,S,D: Movimiento de la camara, INTRO: interactuar";
}

void ScenaMontaje::setup()
{
	// coloca la camara
	camera->moveTo({ 0,0,-100 });

	// boton de confirmar cohete
	Button* but = new Button("Confirmar", this, gPhysics, gScene);
	but->setPosition({ 0,-50,0 });
	but->setShape(CreateShape(PxBoxGeometry(10, 5, 1)), { 10, 5, 1 });
	addGameObject(but);
	gScene->addActor(*but->getActor());
	but->addCallback([this]() {this->saveRocket(); });
	but->addCallback([this]() {this->LaunchScene(); });

	cabina = new ObjetoMovible("mov1", this, gPhysics, gScene, CABINA);
	cabina->setPosition({ 0,20,0 });
	addGameObject(cabina);

	// fondo donde estan los botones
	Widget* fondoBotones = new Widget("fondoBotones", this, { -70, 0, -20 }, 10);
	fondoBotones->setShape(CreateShape(PxBoxGeometry(15, 60, 1)), { 15,60,1 });
	fondoBotones->setColor({ 0.5,1,0.75,1 });
	addGameObject(fondoBotones);

	// botones spawn de modulos
	botonTanque = new Button("BotonTanque", this, gPhysics, gScene);
	botonTanque->setPosition({ -70,20,-10 });
	botonTanque->setShape(CreateShape(PxBoxGeometry(10, 5, 1)), { 10, 5, 1 });
	addGameObject(botonTanque);
	gScene->addActor(*botonTanque->getActor());
	botonTanque->addCallback([this]() {this->creaTanque(); });


	botonPropulsor = new Button("botonPropulsor", this, gPhysics, gScene);
	botonPropulsor->setPosition({ -70,-20,-10 });
	botonPropulsor->setShape(CreateShape(PxBoxGeometry(10, 5, 1)), { 10, 5, 1 });
	addGameObject(botonPropulsor);
	gScene->addActor(*botonPropulsor->getActor());
	botonPropulsor->addCallback([this]() {this->creaPropulsor(); });



#pragma region decoracion
#pragma region Tierra
	RBStatic* PlanetaTierra = new RBStatic("PlanetaTierra", this, gPhysics, gScene);
	PlanetaTierra->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra->setPosition(PlanetaTierra->getPosition() - Vector3(0, RADIO_PLANETA_TIERRA + 50, 0));
	PlanetaTierra->setColor({ 0.75,0.85,1,1 });
	addGameObject(PlanetaTierra);

	RBStatic* PlanetaTierra2 = new RBStatic("PlanetaTierra2", this, gPhysics, gScene);
	PlanetaTierra2->setPosition(PlanetaTierra->getPosition());
	PlanetaTierra2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
	PlanetaTierra2->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra2->setColor({ 0.75,0.75,1,1 });
	addGameObject(PlanetaTierra2);

	RBStatic* PlanetaTierra3 = new RBStatic("PlanetaTierra3", this, gPhysics, gScene);
	PlanetaTierra3->setPosition(PlanetaTierra->getPosition());
	PlanetaTierra3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
	PlanetaTierra3->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra3->setColor({ 0.65,0.75,1,1 });
	addGameObject(PlanetaTierra3);
#pragma endregion
#pragma endregion
}

void ScenaMontaje::show()
{
	Scene::show();
	Cohete = nullptr;
	tamanioCohete = { 0,0,0 };

	// eliminacion de gameobjects del cohete antiguo
	vector<string> aEliminar;
	for (auto go : gameObjects)
	{
		// si es un objeto movible lo elimina
		if (go.second.gameObject->getName().substr(0, 3) == "mov")
			if (((ObjetoMovible*)go.second.gameObject)->getType() != CABINA) aEliminar.push_back(go.second.gameObject->getName());
	}


	for (auto n : aEliminar)
		deleteGameObject(n);
	// reseteo de la cabina
	cabina->reset();


	// settea la posicion de la camara
	camera->moveTo(CAMERA_START_POS);
	camera->lookAt({ 0,0,0 });
	camera->setMovible(true);
	centreVis(true, 1);
}

void ScenaMontaje::creaPropulsor()
{
	ObjetoMovible* propulsor = new ObjetoMovible("propulsor", this, gPhysics, gScene, PROPULSOR);
	propulsor->setPosition(camera->getEye() - CAMERA_START_POS);

	addGameObject(propulsor);
}

void ScenaMontaje::creaTanque()
{
	ObjetoMovible* tanque = new ObjetoMovible("tanque", this, gPhysics, gScene, TANQUE);
	tanque->setPosition(camera->getEye() - CAMERA_START_POS);

	addGameObject(tanque);
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

void ScenaMontaje::keyReleased(unsigned char key, const physx::PxTransform& camera)
{
	Scene::keyReleased(key, camera);

	if (key == 13) {
		if (botonTanque) botonTanque->setPulsado(false);
		if (botonPropulsor) botonPropulsor->setPulsado(false);
	}

}
