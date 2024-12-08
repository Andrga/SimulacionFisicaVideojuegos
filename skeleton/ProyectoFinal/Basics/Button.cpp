#include "Button.h"

Button::Button(string nam, Scene* scn, PxPhysics* gPhysics): RBStatic(nam, scn, gPhysics)
{
	actor->userData = this;
}

Button::~Button()
{
}

void Button::onCollision(GameObject* other)
{
	cout << "colision con boton" << endl;
}
