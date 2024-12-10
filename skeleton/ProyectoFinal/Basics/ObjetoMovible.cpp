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

	moviendo = !moviendo;

	// si estas moviendo a este objeto, y quieres dejar de moverlo:
	if (MovingObj == this && !moviendo) { MovingObj = nullptr, Moving = false; }
	// si no estas moviendo ningun objeto y quieres mover este objeto:
	else if (MovingObj == nullptr && moviendo) { MovingObj = this; Moving = true; }
	// si estoy moviendo otro objeto y quiero mover este:
	else if (MovingObj != this && moviendo) { moviendo = false; return; }


	// si ya esta moviendo un objeto y quiero mover este, moviendo es false y sale del metodo
	if (MovingObj) { moviendo = false; return; }

	cout << (moviendo ? "MOVIENDO EL OBJETO " : "NO MOVIENDO: ") << getName() << endl;

	if (moviendo)
		setPosition({ getPosition().x, getPosition().y, getPosition().z + 10 });
	else
		setPosition({ getPosition().x, getPosition().y, getPosition().z - 10 });
	cout << moviendo << endl;

}