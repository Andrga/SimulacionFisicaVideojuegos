#include "ScenaIntro.h"

void ScenaIntro::setup()
{
	// posicion de la camara
	camera->moveTo({ 0,0,100 });
	camera->lookAt({ 0,0,0 });

	camera->setMovible(true);

	Button* but = new Button("Start", this, gPhysics);
	but->setPosition({ 0,0,0 });
	but->setShape(CreateShape(PxBoxGeometry(1, 10, 10)), { 1, 10, 10 });
	addGameObject(but);
	gScene->addActor(*but->getActor());
	but->addCallback([this]() {this->Start(); });

	//RBDynamic* cosa = new RBDynamic("caja", this, gPhysics);
	//cosa->setPosition({ 0,20,0 });
	//addGameObject(cosa);
	//gScene->addActor(*cosa->getActor());

}

void ScenaIntro::Start()
{
	cout << "Start" << endl;
}
