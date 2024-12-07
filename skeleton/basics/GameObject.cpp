#include "GameObject.h"
#include "Scene.h"

bool GameObject::update(double t) {
	if (!alive) scene->deleteGameObject(name);
	return alive;
};