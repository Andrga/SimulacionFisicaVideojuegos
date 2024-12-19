#include "ScenaIntro.h"
#include "../../basics/SceneManager.h"

void ScenaIntro::setup()
{


	// boton de empezar
	Button* but = new Button("Start", this, gPhysics, gScene);
	but->setPosition({ 0,0,0 });
	but->setColor({ 0.1, 0.8, 0.5, 1 });
	but->setShape(CreateShape(PxBoxGeometry(10, 10, 1)), { 10, 10, 1 });
	addGameObject(but);
	gScene->addActor(*but->getActor());
	but->addCallback([this]() {this->Start(); });

}

void ScenaIntro::Start()
{
	cout << "Start" << endl;
	sceneManager->setScene(1);
}

void ScenaIntro::Quit()
{
	cout << "Quit" << endl;
}

void ScenaIntro::show()
{
	Scene::show();
	display_text1_position = { 100,400 };
	display_text1 = "SPACE EXPLORER SIMULATOR";
	display_text1 += "#<------------------------------->";
	display_text1 += "###->Pulsa <INTRO> con el circulo en el cuadrado del centro";

	display_text2_position = { 10,100 };
	display_text2 = "#CONTROLES";
	display_text2 += "#------------------";
	display_text2 += "#-> Boton Arriba: Crea tanques";
	display_text2 += "#-> Boton Abajo: Crea propulsores";
	display_text2 += "#-> W,A,S,D: Movimiento de la camara#-> INTRO: interactuar";

	// posicion de la camara
	camera->moveTo({ 0,0,100 });
	camera->lookAt({ 0,0,0 });

	camera->setMovible(true);
}
