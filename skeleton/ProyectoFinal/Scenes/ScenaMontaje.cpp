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
	display_text1 += "#Coloca los modulos de la nave a tu antojo";
	display_text1 += "##ASTROS A VISITAR:";
	display_text1 += "#------------------";
	display_text1 += "#      O   <- Venus";
	display_text1 += "#      |   ";
	display_text1 += "#      o   <- Marte";
	display_text1 += "#      |   ";
	display_text1 += "#      .   <- Luna";
	display_text1 += "#      0   <- Tierra";
	display_text2_position = { 10,100 };
	display_text2 = "#CONTROLES";
	display_text2 += "#------------------";
	display_text2 += "#-> Boton Arriba: Crea tanques";
	display_text2 += "#-> Boton Abajo: Crea propulsores";
	display_text2 += "#-> W,A,S,D: Movimiento de la camara#-> INTRO: interactuar";
}

void ScenaMontaje::setup()
{
	// coloca la camara
	camera->moveTo({ 0,0,-100 });

	// boton de confirmar cohete
	Button* but = new Button("Confirmar", this, gPhysics, gScene);
	but->setPosition({ 0,-40,0 });
	but->setShape(CreateShape(PxBoxGeometry(10, 5, 1)), { 10, 5, 1 });
	but->setColor({ 1,0.5,0.5,1 });
	addGameObject(but);
	gScene->addActor(*but->getActor());
	but->addCallback([this]() {this->saveRocket(); });
	but->addCallback([this]() {this->LaunchScene(); });

	// fondo donde estan los botones
	Widget* fondoBotones = new Widget("widfondoBotones", this, { 0, 0, -20 }, 10);
	fondoBotones->setShape(CreateShape(PxBoxGeometry(60, 60, 1)), { 60,60,1 });
	fondoBotones->setColor({ 0.5,1,0.6,1 });
	addGameObject(fondoBotones);

	// botones spawn de modulos
	botonTanque = new Button("BotonTanque", this, gPhysics, gScene);
	botonTanque->setPosition({ -60,20,-10 });
	botonTanque->setShape(CreateShape(PxBoxGeometry(10, 5, 1)), { 10, 5, 1 });
	addGameObject(botonTanque);
	gScene->addActor(*botonTanque->getActor());
	botonTanque->addCallback([this]() {this->creaTanque(); });


	botonPropulsor = new Button("botonPropulsor", this, gPhysics, gScene);
	botonPropulsor->setPosition({ -60,-20,-10 });
	botonPropulsor->setShape(CreateShape(PxBoxGeometry(10, 5, 1)), { 10, 5, 1 });
	addGameObject(botonPropulsor);
	gScene->addActor(*botonPropulsor->getActor());
	botonPropulsor->addCallback([this]() {this->creaPropulsor(); });



#pragma region decoracion
#pragma region Tierra
	RBStatic* PlanetaTierra = new RBStatic("widpltPlanetaTierra", this, gPhysics, gScene);
	PlanetaTierra->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra->setPosition({ 0,-RADIO_PLANETA_TIERRA - 100, 0 });
	PlanetaTierra->setColor({ 0.5,1,0.1,1 });
	addGameObject(PlanetaTierra);

	RBStatic* PlanetaTierra2 = new RBStatic("widpltPlanetaTierra2", this, gPhysics, gScene);
	PlanetaTierra2->setPosition(PlanetaTierra->getPosition());
	PlanetaTierra2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
	PlanetaTierra2->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra2->setColor({ 0.1,1,0.5,1 });
	addGameObject(PlanetaTierra2);

	RBStatic* PlanetaTierra3 = new RBStatic("widpltPlanetaTierra3", this, gPhysics, gScene);
	PlanetaTierra3->setPosition(PlanetaTierra->getPosition());
	PlanetaTierra3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
	PlanetaTierra3->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra3->setColor({ 0.5,1,0.1,1 });
	addGameObject(PlanetaTierra3);

	RBStatic* PlanetaTierra4 = new RBStatic("widpltPlanetaTierra4", this, gPhysics, gScene);
	PlanetaTierra4->setPosition(PlanetaTierra->getPosition());
	PlanetaTierra4->setRotation(PxQuat(PxPi / 2, PxVec3(1, 0, 0)));
	PlanetaTierra4->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra4->setColor({ 0.1,1,0.5,1 });
	addGameObject(PlanetaTierra4);
#pragma endregion
#pragma endregion
}

void ScenaMontaje::show()
{
	Scene::show();
	// tiempo de simulacion al normal
	SimulateTime = 1;

	CoheteInfo = nullptr;
	tamanioCohete = { 0,0,0 };

	// eliminacion de gameobjects del cohete antiguo
	vector<string> aEliminar;
	for (auto go : gameObjects)
	{
		// si es un objeto movible lo elimina
		if (go.second.gameObject->getName().substr(0, 3) == "mov")
			aEliminar.push_back(go.second.gameObject->getName());
	}


	for (auto n : aEliminar)
		deleteGameObject(n);

	cabina = new ObjetoMovible("mov1", this, gPhysics, gScene, CABINA);
	cabina->setPosition({ 0,20,0 });
	addGameObject(cabina);

	// reseteo de la cabina
	cabina->reset();


	// settea la posicion de la camara
	camera->moveTo(CAMERA_START_POS);
	camera->lookAt({ 0,0,0 });
	camera->setMovible(true);
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
	CoheteInfo = cabina->generateModulo();
}

void ScenaMontaje::LaunchScene()
{
	cout << "LAUNCHSCENE" << endl;
	sceneManager->setScene(2);
}

void ScenaMontaje::keyPressed(unsigned char key, const physx::PxTransform& camera)
{
	// boton para poner un cohete predefinido
	if (key == '1') {
		CoheteInfo = &cohetePrefab;
		tamanioCohete = tamanioCohetePrefab;
		cout << "Cohete Prefab1" << endl;
		LaunchScene();
	};

	Scene::keyPressed(key, camera);
}

void ScenaMontaje::keyReleased(unsigned char key, const physx::PxTransform& camera)
{
	Scene::keyReleased(key, camera);

	if (key == 13) {
		if (botonTanque) botonTanque->setPulsado(false);
		if (botonPropulsor) botonPropulsor->setPulsado(false);
	}

}
