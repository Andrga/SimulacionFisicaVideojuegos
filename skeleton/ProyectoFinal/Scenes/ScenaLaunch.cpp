#include "ScenaLaunch.h"
#include "../../basics/SceneManager.h"

void ScenaLaunch::setup()
{
	// setting de la camara
	camera->setMovible(false);

	// sistemas
	fsys = new ForceSystem(this);
	addSystem(fsys);
	psys = new ParticleSystem(this);
	addSystem(psys);

	//psys->addParticleGenerator(new NieblaGen(posIniCabina, 100, psys, this));

	RBStatic* PlanetaTierra = new RBStatic("PlanetaTierra", this, gPhysics, gScene);
	PlanetaTierra->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra->setColor({ 0.75,0.85,1,1 });
	addGameObject(PlanetaTierra);
	fsys->addForceGenerator(new GravedadPlanetaGenerator({ 0,0,0 }, this, -9.8, RADIO_GRAVEDAD_TIERRA, RADIO_PLANETA_TIERRA + 100));

#pragma region subdivisiones de la esfera del planeta
	RBStatic* PlanetaTierra2 = new RBStatic("PlanetaTierra2", this, gPhysics, gScene);
	PlanetaTierra2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
	PlanetaTierra2->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra2->setColor({ 0.75,0.75,1,1 });
	addGameObject(PlanetaTierra2);

	RBStatic* PlanetaTierra3 = new RBStatic("PlanetaTierra3", this, gPhysics, gScene);
	PlanetaTierra3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
	PlanetaTierra3->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra3->setColor({ 0.65,0.75,1,1 });
	addGameObject(PlanetaTierra3);
#pragma endregion

	// plataforma de lanzamiento del cohete
	PlataformaLanzamiento = new RBStatic("PlataformaLanzamiento", this, gPhysics, gScene);
	PlataformaLanzamiento->setPosition({ posIniCabina.x ,RADIO_PLANETA_TIERRA + 5, posIniCabina.z });
	PlataformaLanzamiento->setShape(CreateShape(PxBoxGeometry(tamanioCohete.x + 5, 5, tamanioCohete.x + 5)), { tamanioCohete.x + 5, 5, tamanioCohete.x + 5 });
	PlataformaLanzamiento->setColor({ 1,1,1,1 });
	addGameObject(PlataformaLanzamiento);



}

void ScenaLaunch::montarCohete()
{
	cabina = new Modulo("Cabina", this, gPhysics, gScene, Cohete->tipo, nullptr);

	posIniCabina.y = RADIO_PLANETA_TIERRA + tamanioCohete.y + 5;
	cabina->setPosition(posIniCabina);

	// crea los modulos colindantes	
	if (Cohete->derecha)
	{
		Cohete->derecha->izquierda = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* derecha = new Modulo("derecha", this, gPhysics, gScene, Cohete->derecha->tipo, cabina);
		derecha->setPosition({ cabina->getPosition().x + sizeModul,cabina->getPosition().y ,cabina->getPosition().z });
		montarCoheteRec(Cohete->derecha, derecha);
		// unimos los modulos por gomas elasticas
		if (derecha) {
			fsys->addForceGenerator(new GomaGenerator(this, TENSION_ENTRE_MODULOS, sizeModul, derecha, cabina));
			addGameObject(derecha);
			// si es un propulsor aniadimos sistema de particulas para la propulsion
			if (Cohete->derecha->tipo == PROPULSOR)
				psys->addParticleGenerator(new PropulsionParticleGen(derecha->getPosition(), 100, psys, this, gPhysics, gScene, &porcentajeFuerzProp, derecha));
		}
	}
	if (Cohete->abajo) {
		Cohete->abajo->arriba = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* abajo = new Modulo("abajo", this, gPhysics, gScene, Cohete->abajo->tipo, cabina);
		abajo->setPosition({ cabina->getPosition().x ,cabina->getPosition().y - sizeModul,cabina->getPosition().z });
		montarCoheteRec(Cohete->abajo, abajo);
		// unimos los modulos por gomas elasticas
		if (abajo) {
			fsys->addForceGenerator(new GomaGenerator(this, TENSION_ENTRE_MODULOS, sizeModul, abajo, cabina));
			addGameObject(abajo);
			// si es un propulsor aniadimos sistema de particulas para la propulsion
			if (Cohete->abajo->tipo == PROPULSOR)
				psys->addParticleGenerator(new PropulsionParticleGen(abajo->getPosition(), 100, psys, this, gPhysics, gScene, &porcentajeFuerzProp, abajo));
		}
	}
	if (Cohete->izquierda) {
		Cohete->izquierda->derecha = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* izquierda = new Modulo("izquierda", this, gPhysics, gScene, Cohete->izquierda->tipo, cabina);
		izquierda->setPosition({ cabina->getPosition().x - sizeModul,cabina->getPosition().y ,cabina->getPosition().z });
		montarCoheteRec(Cohete->izquierda, izquierda);
		// unimos los modulos por gomas elasticas
		if (izquierda) {
			fsys->addForceGenerator(new GomaGenerator(this, TENSION_ENTRE_MODULOS, sizeModul, izquierda, cabina));
			addGameObject(izquierda);
			// si es un propulsor aniadimos sistema de particulas para la propulsion
			if (Cohete->izquierda->tipo == PROPULSOR)
				psys->addParticleGenerator(new PropulsionParticleGen(izquierda->getPosition(), 100, psys, this, gPhysics, gScene, &porcentajeFuerzProp, izquierda));
		}
	}
	if (Cohete->arriba) {
		Cohete->arriba->abajo = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* arriba = new Modulo("arriba", this, gPhysics, gScene, Cohete->arriba->tipo, cabina);
		arriba->setPosition({ cabina->getPosition().x ,cabina->getPosition().y + sizeModul,cabina->getPosition().z });
		montarCoheteRec(Cohete->arriba, arriba);
		// unimos los modulos por gomas elasticas
		if (arriba) {
			fsys->addForceGenerator(new GomaGenerator(this, TENSION_ENTRE_MODULOS, sizeModul, arriba, cabina));
			addGameObject(arriba);
			// si es un propulsor aniadimos sistema de particulas para la propulsion
			if (Cohete->arriba->tipo == PROPULSOR)
				psys->addParticleGenerator(new PropulsionParticleGen(arriba->getPosition(), 100, psys, this, gPhysics, gScene, &porcentajeFuerzProp, arriba));

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
		derecha->setPosition({ actualMod->getPosition().x + sizeModul,actualMod->getPosition().y,actualMod->getPosition().z });
		montarCoheteRec(modulo->derecha, derecha);
		// unimos los modulos por gomas elasticas
		if (derecha) {
			fsys->addForceGenerator(new GomaGenerator(this, TENSION_ENTRE_MODULOS, sizeModul, derecha, actualMod));
			addGameObject(derecha);
			// si es un propulsor aniadimos sistema de particulas para la propulsion
			if (modulo->derecha->tipo == PROPULSOR)
				psys->addParticleGenerator(new PropulsionParticleGen(derecha->getPosition(), 100, psys, this, gPhysics, gScene, &porcentajeFuerzProp, derecha));
		}
	}
	if (modulo->abajo) {
		modulo->abajo->arriba = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* abajo = new Modulo("abajo", this, gPhysics, gScene, modulo->abajo->tipo, cabina);
		abajo->setPosition({ actualMod->getPosition().x,actualMod->getPosition().y - sizeModul,actualMod->getPosition().z });
		montarCoheteRec(modulo->abajo, abajo);
		// unimos los modulos por gomas elasticas
		if (abajo) {
			fsys->addForceGenerator(new GomaGenerator(this, TENSION_ENTRE_MODULOS, sizeModul, abajo, actualMod));
			addGameObject(abajo);
			// si es un propulsor aniadimos sistema de particulas para la propulsion
			if (modulo->abajo->tipo == PROPULSOR)
				psys->addParticleGenerator(new PropulsionParticleGen(abajo->getPosition(), 100, psys, this, gPhysics, gScene, &porcentajeFuerzProp, abajo));
		}
	}
	if (modulo->izquierda) {
		modulo->izquierda->derecha = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* izquierda = new Modulo("izquierda", this, gPhysics, gScene, modulo->izquierda->tipo, cabina);
		izquierda->setPosition({ actualMod->getPosition().x - sizeModul,actualMod->getPosition().y,actualMod->getPosition().z });
		montarCoheteRec(modulo->izquierda, izquierda);
		// unimos los modulos por gomas elasticas
		if (izquierda) {
			fsys->addForceGenerator(new GomaGenerator(this, TENSION_ENTRE_MODULOS, sizeModul, izquierda, actualMod));
			addGameObject(izquierda);
			// si es un propulsor aniadimos sistema de particulas para la propulsion
			if (modulo->izquierda->tipo == PROPULSOR)
				psys->addParticleGenerator(new PropulsionParticleGen(izquierda->getPosition(), 100, psys, this, gPhysics, gScene, &porcentajeFuerzProp, izquierda));
		}
	}
	if (modulo->arriba) {
		modulo->arriba->abajo = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* arriba = new Modulo("arriba", this, gPhysics, gScene, modulo->arriba->tipo, cabina);
		arriba->setPosition({ actualMod->getPosition().x,actualMod->getPosition().y + sizeModul,actualMod->getPosition().z });
		montarCoheteRec(modulo->derecha, arriba);
		// unimos los modulos por gomas elasticas
		if (arriba) {
			fsys->addForceGenerator(new GomaGenerator(this, TENSION_ENTRE_MODULOS, sizeModul, arriba, actualMod));
			addGameObject(arriba);
			// si es un propulsor aniadimos sistema de particulas para la propulsion
			if (modulo->arriba->tipo == PROPULSOR)
				psys->addParticleGenerator(new PropulsionParticleGen(arriba->getPosition(), 100, psys, this, gPhysics, gScene, &porcentajeFuerzProp, arriba));
		}
	}

	return actualMod;

}

void ScenaLaunch::propulsar(Vector3 impulseRotation)
{
	DirPropulsion = impulseRotation;
	for (auto o : gameObjects) {
		// si o no es un modulo de cohete, ni un propulsor lo salta
		if (o.second.gameObject->getName().substr(0, 3) == "mod" && ((Modulo*)o.second.gameObject)->getTipo() == PROPULSOR) {
			// setting de la direccion en la que propulsar
			PxVec3 globalDirection = ((Modulo*)o.second.gameObject)->getActor()->getGlobalPose().q.rotate({ 0,1,0 });

			// si hay rotacion por input se aniade rotacion adicional
			if (impulseRotation.x != 0 || impulseRotation.z != 0)
			{
				PxQuat aditionalRotation(PxPi * 30 / 180, impulseRotation);
				globalDirection = aditionalRotation.rotate(globalDirection);

			}


			o.second.gameObject->addForce(globalDirection * (FUERZA_PROPULSOR * porcentajeFuerzProp));
		}

	}
}

void ScenaLaunch::keyPressed(unsigned char key, const physx::PxTransform& camera)
{
	// propulsa si he pulsado el intro
	if (key == 13)
		propulsando = true;


	switch (key)
	{
		// aumentar disminuir potencia de impulso
	case'i':
		if (porcentajeFuerzProp < 1) porcentajeFuerzProp += 0.01;
		else porcentajeFuerzProp = 1;
		break;
	case'k':
		if (porcentajeFuerzProp > 0) porcentajeFuerzProp -= 0.01;
		else porcentajeFuerzProp = 0;
		break;
		// zoom
	case'o':
		zoom += 10;
		if (abs(zoom) >= 1260) centreVis(true, 1);
		else centreVis(false, 1);
		break;
	case'l':
		zoom -= 10;
		if (abs(zoom) >= 1260)
			centreVis(true, -1);
		else
			centreVis(false, -1);
		break;
		// direccion de impulso
	case'w':
		propulsar({ 1,0,0 });
		break;
	case's':
		propulsar({ -1,0,0 });
		break;
	case'a':
		propulsar({ 0,0,-1 });
		break;
	case'd':
		propulsar({ 0,0,1 });
		break;
		// volver a la zona de montaje
	case'q':
		cout << "Start" << endl;
		sceneManager->setScene(1);
		break;
	default:
		break;
	}
}

void ScenaLaunch::keyReleased(unsigned char key, const physx::PxTransform& camera)
{
	// deja de propulsar al levantar la tecla
	if (key == 13)
		propulsando = false;
}


void ScenaLaunch::update(double t)
{
	Scene::update(t);
	if (cabina) {
		PxVec3 globalDirection = (cabina->getActor()->getGlobalPose().q.rotate({ 0,0,-1 }));

		//camera->moveTo((globalDirection * 100) + cabina->getPosition());

		camera->moveTo(cabina->getPosition() + Vector3(cameraOffset.x, cameraOffset.y, cameraOffset.z + zoom));
		camera->lookAt(cabina->getPosition());
	}

	if (propulsando) propulsar({ 0,0,0 });

	// texto con informacion
	display_text1_position = { 10,500 };
	display_text1 = "LANZAMIENTO";
	display_text1 += "#------------------------";
	display_text1 += "#-Planeta Actual: ";
	display_text1 += "#-Potencia Proulsores: " + to_string(porcentajeFuerzProp * 100) + "%";
	if (cabina) display_text1 += "#-Fuerza Aplicada: " + to_string(cabina->getActualForce().x) + "||" + to_string(cabina->getActualForce().y) + "||" + to_string(cabina->getActualForce().z);
	display_text1 += "#-Direccion Propulsion: X:" + to_string((int)DirPropulsion.x) + " Z: " + to_string((int)DirPropulsion.z);
	display_text1 += "#-Zoom: " + to_string((int)zoom);

	display_text2_position = { 10,100 };
	display_text2 = "CONTROLES:";
	display_text2 += "#------------------------";
	display_text2 += "#-INTRO: propulsar#-I: Aumento potencia, K: Disminuye potencia#-A: Inclinacion Izquierda, D: InclinacionDerecha";

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

	// definimos el tamanio y la forma de la plataforma de lanzamiento segun el tamanio del cohete
	PlataformaLanzamiento->setShape(CreateShape(PxBoxGeometry(tamanioCohete.x + 5, 5, tamanioCohete.x + 5)), { tamanioCohete.x + 5, 5, tamanioCohete.x + 5 });
}
