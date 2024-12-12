#include "ScenaLaunch.h"

void ScenaLaunch::setup()
{
	// setting de la camara
	camera->setMovible(false);
	fsys = new ForceSystem(this);
	addSystem(fsys);

	RBStatic* PlanetaTierra = new RBStatic("PlanetaTierra", this, gPhysics, gScene);
	PlanetaTierra->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra->setColor({ 0.75,0.75,1,1 });
	addGameObject(PlanetaTierra);

	// plataforma de lanzamiento del cohete
	RBStatic* PlataformaLanzamiento = new RBStatic("PlataformaLanzamiento", this, gPhysics, gScene);
	PlataformaLanzamiento->setPosition({ posIniCabina.x ,RADIO_PLANETA_TIERRA, posIniCabina.z });
	PlataformaLanzamiento->setShape(CreateShape(PxBoxGeometry(20, 5, 20)), { 20, 5, 20 });
	PlataformaLanzamiento->setColor({ 1,1,1,1 });
	addGameObject(PlataformaLanzamiento);


	fsys->addForceGenerator(new GravedadPlanetaGenerator({ 0,0,0 }, this, -9.8, RADIO_GRAVEDAD_TIERRA, RADIO_PLANETA_TIERRA));

}

void ScenaLaunch::montarCohete()
{
	cabina = new Modulo("Cabina", this, gPhysics, gScene, Cohete->tipo, nullptr);

	posIniCabina.y = RADIO_PLANETA_TIERRA + tamanioCohete.y;
	cabina->setPosition(posIniCabina);

	// crea los modulos colindantes	
	if (Cohete->derecha)
	{
		Cohete->derecha->izquierda = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* derecha = new Modulo("derecha", this, gPhysics, gScene, Cohete->derecha->tipo, cabina);
		derecha->setPosition({ cabina->getPosition().x + 11,cabina->getPosition().y ,cabina->getPosition().z });
		montarCoheteRec(Cohete->derecha, derecha);
		// unimos los modulos por gomas elasticas
		if (derecha) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 11, derecha, cabina));
			addGameObject(derecha);
		}
	}
	if (Cohete->abajo) {
		Cohete->abajo->arriba = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* abajo = new Modulo("abajo", this, gPhysics, gScene, Cohete->abajo->tipo, cabina);
		abajo->setPosition({ cabina->getPosition().x ,cabina->getPosition().y - 11,cabina->getPosition().z });
		montarCoheteRec(Cohete->abajo, abajo);
		// unimos los modulos por gomas elasticas
		if (abajo) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 11, abajo, cabina));
			addGameObject(abajo);
		}
	}
	if (Cohete->izquierda) {
		Cohete->izquierda->derecha = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* izquierda = new Modulo("izquierda", this, gPhysics, gScene, Cohete->izquierda->tipo, cabina);
		izquierda->setPosition({ cabina->getPosition().x - 11,cabina->getPosition().y ,cabina->getPosition().z });
		montarCoheteRec(Cohete->izquierda, izquierda);
		// unimos los modulos por gomas elasticas
		if (izquierda) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 11, izquierda, cabina));
			addGameObject(izquierda);
		}
	}
	if (Cohete->arriba) {
		Cohete->arriba->abajo = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* arriba = new Modulo("arriba", this, gPhysics, gScene, Cohete->arriba->tipo, cabina);
		arriba->setPosition({ cabina->getPosition().x ,cabina->getPosition().y + 11,cabina->getPosition().z });
		montarCoheteRec(Cohete->arriba, arriba);
		// unimos los modulos por gomas elasticas
		if (arriba) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 11, arriba, cabina));
			addGameObject(arriba);
		}
	}

	addGameObject(cabina);
}

Modulo* ScenaLaunch::montarCoheteRec(ModuloInfo* modulo, Modulo* actualMod)
{
	// si no hay modulo info entonces no puede crear modulo
	if (modulo == nullptr) return nullptr;


	//crea los modulos colindantes	
	if (modulo->derecha)
	{
		modulo->derecha->izquierda = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* derecha = new Modulo("derecha", this, gPhysics, gScene, modulo->derecha->tipo, cabina);
		derecha->setPosition({ actualMod->getPosition().x + 11,actualMod->getPosition().y,actualMod->getPosition().z });
		montarCoheteRec(modulo->derecha, derecha);
		// unimos los modulos por gomas elasticas
		if (derecha) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 11, derecha, actualMod));
			addGameObject(derecha);
		}
	}
	if (modulo->abajo) {
		modulo->abajo->arriba = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* abajo = new Modulo("abajo", this, gPhysics, gScene, modulo->abajo->tipo, cabina);
		abajo->setPosition({ actualMod->getPosition().x,actualMod->getPosition().y - 11,actualMod->getPosition().z });
		montarCoheteRec(modulo->abajo, abajo);
		// unimos los modulos por gomas elasticas
		if (abajo) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 11, abajo, actualMod));
			addGameObject(abajo);
		}
	}
	if (modulo->izquierda) {
		modulo->izquierda->derecha = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* izquierda = new Modulo("izquierda", this, gPhysics, gScene, modulo->izquierda->tipo, cabina);
		izquierda->setPosition({ actualMod->getPosition().x - 11,actualMod->getPosition().y,actualMod->getPosition().z });
		montarCoheteRec(modulo->izquierda, izquierda);
		// unimos los modulos por gomas elasticas
		if (izquierda) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 11, izquierda, actualMod));
			addGameObject(izquierda);
		}
	}
	if (modulo->arriba) {
		modulo->arriba->abajo = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* arriba = new Modulo("arriba", this, gPhysics, gScene, modulo->arriba->tipo, cabina);
		arriba->setPosition({ actualMod->getPosition().x,actualMod->getPosition().y + 11,actualMod->getPosition().z });
		montarCoheteRec(modulo->derecha, arriba);
		// unimos los modulos por gomas elasticas
		if (arriba) {
			fsys->addForceGenerator(new GomaGenerator(this, 1000, 11, arriba, actualMod));
			addGameObject(arriba);
		}
	}

	return actualMod;

}

void ScenaLaunch::propulsar()
{
	for (auto o : gameObjects) {
		// si o no es un modulo de cohete, ni un propulsor lo salta
		if (o.second.gameObject->getName().substr(0, 3) == "mod" && ((Modulo*)o.second.gameObject)->getTipo() == PROPULSOR) {
			PxVec3 globalDirection = ((Modulo*)o.second.gameObject)->getActor()->getGlobalPose().q.rotate({ 0,1,0 });

			o.second.gameObject->addForce(globalDirection * (FUERZA_PROPULSOR * porcentajeFuerzProp));
		}

	}
}

void ScenaLaunch::keyPressed(unsigned char key, const physx::PxTransform& camera)
{
	switch (key)
	{
	case 13:
		propulsar();
		break;
	case'w':
		if (porcentajeFuerzProp < 1) porcentajeFuerzProp += 0.01;
		break;
	case's':
		if (porcentajeFuerzProp > 0) porcentajeFuerzProp -= 0.01;
		break;

	default:
		break;
	}
}

void ScenaLaunch::update(double t)
{
	Scene::update(t);
	if (cabina) {
		PxVec3 globalDirection = (cabina->getActor()->getGlobalPose().q.rotate({ 0,0,-1 }));

		camera->moveTo((globalDirection * 100) + cabina->getPosition());

		//camera->setDir(globalDirection);
		camera->lookAt(cabina->getPosition());
	}


	// texto con informacion
	display_text_position = { 20,150 };
	display_text = "LANZAMIENTO";
	display_text += "#------------------------";
	display_text += "#-Planeta Actual: ";
	display_text += "#-Potencia Proulsores: " + to_string(porcentajeFuerzProp * 100) + "%";
	display_text += "##CONTROLES:";
	display_text += "#------------------------";
	display_text += "#-INTRO: propulsar#-W: Aumento potencia, S: Disminuye potencia#-A: Inclinacion Izquierda, D: InclinacionDerecha";

}

void ScenaLaunch::show()
{
	Scene::show();

	// setteo de la camara
	montarCohete();
	camera->setMovible(false);
	camera->moveTo({ cabina->getPosition().x, cabina->getPosition().y, cabina->getPosition().z + 100 });

	// definimos la gravedad en esta escena
	gScene->setGravity({ 0,0,0 });
}
