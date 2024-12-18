#include "GameObject.h"
#include "Scene.h"

bool GameObject::update(double t) {
	if (startlifeTime >= 0 && lifeTime > startlifeTime)
	{
		alive = false;
		return false;
	}
	else if (startlifeTime >= 0)
		lifeTime += t;

	return true;
}
void GameObject::setShape(PxShape* shp, Vector3 siz) {
	renderItem->shape = shp;
	shape = shp;
	size = siz;
}

void GameObject::setShape(PxShape* shp)
{
	renderItem->shape = shp;
}
