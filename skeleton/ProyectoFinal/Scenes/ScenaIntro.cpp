#include "ScenaIntro.h"

void ScenaIntro::setup()
{
	// posicion de la camara
	camera->moveTo({0,0,100});
	camera->lookAt({0,0,0});

	camera->setMovible(true);
}
