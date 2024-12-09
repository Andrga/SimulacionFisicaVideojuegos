#include "GameObject.h"
#include "Scene.h"

bool GameObject::update(double t) {
	if (!alive) scene->deleteGameObject(name);
	return alive;
}
void GameObject::setShape(PxShape* shp, Vector3 siz) {
	renderItem->shape = shp; 
	shape = shp; 
	size = siz;
}