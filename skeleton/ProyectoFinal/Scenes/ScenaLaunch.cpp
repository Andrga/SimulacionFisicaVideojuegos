#include "ScenaLaunch.h"

void ScenaLaunch::setup()
{
	// setting de la camara
	camera->setMovible(false);
	fsys = new ForceSystem(this);
	addSystem(fsys);

}

void ScenaLaunch::montarCohete()
{
	cabina = new Modulo("Cabina", this, gPhysics, gScene, Cohete->tipo);
	// creamos los modulos colindantes
	//crea los modulos colindantes	
	if (Cohete->derecha)
	{
		Cohete->derecha->izquierda = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* derecha = montarCoheteRec(Cohete->derecha);
		// unimos los modulos por gomas elasticas
		if (derecha) {
			fsys->addForceGenerator(new GomaGenerator(this, 100, 10, derecha, cabina));
			addGameObject(derecha);
		}
	}
	if (Cohete->abajo) {
		Cohete->abajo->arriba = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* abajo = montarCoheteRec(Cohete->abajo);
		// unimos los modulos por gomas elasticas
		if (abajo) {
			fsys->addForceGenerator(new GomaGenerator(this, 100, 10, abajo, cabina));
			addGameObject(abajo);
		}
	}
	if (Cohete->izquierda) {
		Cohete->izquierda->derecha = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* izquierda = montarCoheteRec(Cohete->izquierda);
		// unimos los modulos por gomas elasticas
		if (izquierda) {
			fsys->addForceGenerator(new GomaGenerator(this, 100, 10, izquierda, cabina));
			addGameObject(izquierda);
		}
	}
	if (Cohete->arriba) {
		Cohete->arriba->abajo = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* arriba = montarCoheteRec(Cohete->arriba);
		// unimos los modulos por gomas elasticas
		if (arriba) {
			fsys->addForceGenerator(new GomaGenerator(this, 100, 10, arriba, cabina));
			addGameObject(arriba);
		}
	}

	addGameObject(cabina);
}

Modulo* ScenaLaunch::montarCoheteRec(ModuloInfo* modulo)
{
	// si no hay modulo info entonces no puede crear modulo
	if (modulo == nullptr) return nullptr;

	// crea el modulo actual
	Modulo* actualMod = new Modulo("mod", this, gPhysics, gScene, modulo->tipo);

	//crea los modulos colindantes	
	if (modulo->derecha)
	{
		modulo->derecha->izquierda = nullptr; // eliminamos la referencia al modulo base para que no lo cree nuevamente en el metodo recursivo
		Modulo* derecha = montarCoheteRec(modulo->derecha);
		// unimos los modulos por gomas elasticas
		if (derecha) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 10, derecha, actualMod));
			derecha->setPosition({ actualMod->getPosition().x + 10, actualMod->getPosition().y, actualMod->getPosition().z });
			addGameObject(derecha);
		}
	}
	if (modulo->abajo) {
		modulo->abajo->arriba = nullptr; // eliminamos la referencia al modulo base para que no lo cree nuevamente en el metodo recursivo
		Modulo* abajo = montarCoheteRec(modulo->abajo);
		// unimos los modulos por gomas elasticas
		if (abajo) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 10, abajo, actualMod));
			abajo->setPosition({ actualMod->getPosition().x, actualMod->getPosition().y - 10, actualMod->getPosition().z });
			addGameObject(abajo);
		}
	}
	if (modulo->izquierda) {
		modulo->izquierda->derecha = nullptr; // eliminamos la referencia al modulo base para que no lo cree nuevamente en el metodo recursivo
		Modulo* izquierda = montarCoheteRec(modulo->izquierda);
		// unimos los modulos por gomas elasticas
		if (izquierda) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 10, izquierda, actualMod));
			izquierda->setPosition({ actualMod->getPosition().x - 10, actualMod->getPosition().y, actualMod->getPosition().z });
			addGameObject(izquierda);
		}
	}
	if (modulo->arriba) {
		modulo->arriba->abajo = nullptr; // eliminamos la referencia al modulo base para que no lo cree nuevamente en el metodo recursivo
		Modulo* arriba = montarCoheteRec(modulo->arriba);
		// unimos los modulos por gomas elasticas
		if (arriba) {
			fsys->addForceGenerator(new GomaGenerator(this, 100, 10, arriba, actualMod));
			arriba->setPosition({ actualMod->getPosition().x, actualMod->getPosition().y + 10, actualMod->getPosition().z });
			addGameObject(arriba);
		}
	}

	return actualMod;

}

void ScenaLaunch::update(double t)
{
	Scene::update(t);
	if (cabina)camera->moveTo({ cabina->getPosition().x ,cabina->getPosition().y ,cabina->getPosition().z + 100 });
}

void ScenaLaunch::show()
{
	Scene::show();

	montarCohete();
	camera->setMovible(false);
	camera->moveTo({ cabina->getPosition().x, cabina->getPosition().y, cabina->getPosition().z + 100 });
}
