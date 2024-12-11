#include "ScenaIntro.h"
#include "../../basics/SceneManager.h"

void ScenaIntro::setup()
{
	

	// boton de empezar
	Button* but = new Button("Start", this, gPhysics, gScene);
	but->setPosition({ 0,0,0 });
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

	// posicion de la camara
	camera->moveTo({ 0,0,100 });
	camera->lookAt({ 0,0,0 });

	camera->setMovible(true);
}
