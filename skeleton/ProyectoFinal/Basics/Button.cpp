#include "Button.h"

Button::Button(string nam, Scene* scn, PxPhysics* gPhysics): RBStatic(nam, scn, gPhysics)
{

}

Button::~Button()
{
}

void Button::onCollision(GameObject* other)
{
	if (!pulsado)
	{
		GameObject::onCollision(other);
		pulsado = true;
	}
	else
		cout << "Boton ya pulsado" << endl;
}

void Button::setVisibility(bool vis)
{
	RBStatic::setVisibility(vis);
	// resetea el estado del boton
	if (vis) pulsado = false;
}
