#include "ScenaMontaje.h"

void ScenaMontaje::setup()
{
	GameObject* movible1 = new ObjetoMovible("mov1", this, gPhysics, gScene);
	movible1->setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5, 5, 5 });
	movible1->setPosition({ -20,20,0 });
	movible1->setColor({ 1,0,0,1 });

	addGameObject(movible1); 

	GameObject* movible2 = new ObjetoMovible("mov2", this, gPhysics, gScene);
	movible2->setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5, 5, 5 });
	movible2->setPosition({ 0,20,0 });
	movible2->setColor({ 0,1,0,1 });

	addGameObject(movible2);
	
	GameObject* movible3 = new ObjetoMovible("mov3", this, gPhysics, gScene);
	movible3->setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5, 5, 5 });
	movible3->setPosition({ 20,20,0 });
	movible3->setColor({ 0,0,1,1 });

	addGameObject(movible3);
}
