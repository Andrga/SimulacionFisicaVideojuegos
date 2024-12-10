#include "ObjetoMovible.h"

ObjetoMovible::ObjetoMovible(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene) : RBStatic(nam, scn, gPhysics,gScene){
	// aniade el callback para alternar si se esta arrastrando el modulo o no
	addCallback([this]() {this->alternateMoviendo(); });
}

bool ObjetoMovible::update(double t)
{

	// si estoy arrastrando al modulo sigue a la camara
	if (moviendo) {
		setPosition({ GetCamera()->getEye().x,  GetCamera()->getEye().y, getPosition().z });
		//cout << "MOVIENDOOOO--" << endl;
	}

	return RBActor::update(t);
}

void ObjetoMovible::alternateMoviendo() {

	cout << "moviendo" << endl;
	moviendo = !moviendo;
	if (moviendo)
		setPosition({ getPosition().x, getPosition().y, getPosition().z + 10 });
	else
		setPosition({ getPosition().x, getPosition().y, getPosition().z - 10 });
	cout << moviendo << endl;
}