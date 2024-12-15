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

	cameraAnchor = new RBDynamic("widCameraFollow", this, gPhysics, gScene);
	cameraAnchor->setStartLifeTime(-1);
	cameraAnchor->setShape(CreateShape(PxSphereGeometry(0.1)), { 0, 0, 0 });
	cameraAnchor->getActor().damping
	addGameObject(cameraAnchor);


	//psys->addParticleGenerator(new NieblaGen(posIniCabina, 100, psys, this));


#pragma region subdivisiones de la esfera del planeta

	RBStatic* PlanetaTierra = new RBStatic("PlanetaTierra", this, gPhysics, gScene);
	PlanetaTierra->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra->setColor({ 0.75,0.85,1,1 });
	addGameObject(PlanetaTierra);

	RBStatic* PlanetaTierra2 = new RBStatic("PlanetaTierra2", this, gPhysics, gScene);
	PlanetaTierra2->setPosition(PlanetaTierra->getPosition());
	PlanetaTierra2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
	PlanetaTierra2->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra2->setColor({ 0.75,0.75,1,1 });
	addGameObject(PlanetaTierra2);

	RBStatic* PlanetaTierra3 = new RBStatic("PlanetaTierra3", this, gPhysics, gScene);
	PlanetaTierra3->setPosition(PlanetaTierra->getPosition());
	PlanetaTierra3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
	PlanetaTierra3->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
	PlanetaTierra3->setColor({ 0.65,0.75,1,1 });
	addGameObject(PlanetaTierra3);


	// gravedad de planeta tierra
	fsys->addForceGenerator(new GravedadPlanetaGenerator(PlanetaTierra->getPosition(), this, -9.8, RADIO_GRAVEDAD_TIERRA, RADIO_PLANETA_TIERRA + 100));
#pragma endregion
#pragma region Luna

	RBStatic* Luna1 = new RBStatic("Luna1", this, gPhysics, gScene);
	Luna1->setShape(CreateShape(PxSphereGeometry(RADIO_LUNA)), { RADIO_LUNA, RADIO_LUNA, RADIO_LUNA });
	Luna1->setPosition(Vector3(0, RADIO_GRAVEDAD_TIERRA + RADIO_LUNA + 100, 0));
	Luna1->setColor({ 0.75,0.85,1,1 });
	addGameObject(Luna1);

	RBStatic* Luna2 = new RBStatic("Luna2", this, gPhysics, gScene);
	Luna2->setPosition(Luna1->getPosition());
	Luna2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
	Luna2->setShape(CreateShape(PxSphereGeometry(RADIO_LUNA)), { RADIO_LUNA, RADIO_LUNA, RADIO_LUNA });
	Luna2->setColor({ 0.75,0.75,1,1 });
	addGameObject(Luna2);

	RBStatic* Luna3 = new RBStatic("Luna3", this, gPhysics, gScene);
	Luna3->setPosition(Luna1->getPosition());
	Luna3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
	Luna3->setShape(CreateShape(PxSphereGeometry(RADIO_LUNA)), { RADIO_LUNA, RADIO_LUNA, RADIO_LUNA });
	Luna3->setColor({ 0.65,0.75,1,1 });
	addGameObject(Luna3);


	// GRAVEDAD DE LA LUNA
	fsys->addForceGenerator(new GravedadPlanetaGenerator(Luna1->getPosition(), this, -1.62f, RADIO_GRAVEDAD_LUNA, RADIO_LUNA + 100));
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
	addGameObject(cabina);

	montarCoheteRec(Cohete, cabina);

}

Modulo* ScenaLaunch::montarCoheteRec(ModuloInfo* modulo, Modulo* actualMod)
{
	// si no hay modulo info entonces no puede crear modulo
	if (modulo == nullptr) return nullptr;


	//crea los modulos colindantes	
	if (modulo->derecha)
	{
		modulo->derecha->izquierda = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* derecha = creaModulo(modulo->derecha, actualMod, { -1,0,0 });
		montarCoheteRec(modulo->derecha, derecha);
	}
	if (modulo->abajo) {
		modulo->abajo->arriba = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* abajo = creaModulo(modulo->abajo, actualMod, { 0,1,0 });
		montarCoheteRec(modulo->abajo, abajo);
	}
	if (modulo->izquierda) {
		modulo->izquierda->derecha = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* izquierda = creaModulo(modulo->izquierda, actualMod, { 1,0,0 });
		montarCoheteRec(modulo->izquierda, izquierda);
	}
	if (modulo->arriba) {
		modulo->arriba->abajo = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* arriba = creaModulo(modulo->arriba, actualMod, { 0,-1,0 });
		montarCoheteRec(modulo->derecha, arriba);
	}

	return actualMod;

}

Modulo* ScenaLaunch::creaModulo(ModuloInfo* modulo, Modulo* actualMod, Vector3 dir)
{
	Modulo* mod = new Modulo("nuevo", this, gPhysics, gScene, modulo->tipo, cabina);
	mod->setPosition(actualMod->getPosition() + (dir * sizeModul));

	// unimos los modulos por fixedJoints
	PxFixedJoint* fixedJoint = PxFixedJointCreate(*gPhysics,
		actualMod->getActor(), PxTransform(PxVec3(0.0f, 0.0f, 0.0f)),
		mod->getActor(), PxTransform(dir * sizeModul));
	// aniade el gameobject
	addGameObject(mod);

	// si es un propulsor aniadimos sistema de particulas para la propulsion
	if (modulo->tipo == PROPULSOR)
		partGenerators.push_back(new PropulsionParticleGen(mod->getPosition(), 10, psys, this, gPhysics, gScene, &porcentajeFuerzProp, mod));

	return mod;
}

void ScenaLaunch::propulsar(Vector3 impulseRotation)
{
	DirPropulsion = impulseRotation;

	for (auto pg : partGenerators)
		pg->startGenerate();

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
	if (key == 13) {
		if (!introPulsed)
		{
			propulsando = !propulsando;
			introPulsed = true;
		}
	}
	// aumentar disminuir potencia de impulso
	if (key == 'i') {
		if (porcentajeFuerzProp < 1) porcentajeFuerzProp += 0.01;
		else porcentajeFuerzProp = 1;
	}
	if (key == 'k') {
		if (porcentajeFuerzProp > 0) porcentajeFuerzProp -= 0.01;
		else porcentajeFuerzProp = 0;
	}
	// zoom
	if (key == 'o') {
		zoomFactor++;
		zoom = zoomFactor * zoomVel;
		if (abs(zoom) >= 1260) centreVis(true, 1);
		else centreVis(false, 1);
	}
	if (key == 'l') {
		zoomFactor--;
		zoom = zoomFactor * zoomVel;
		if (abs(zoom) >= 1260)
			centreVis(true, -1);
		else
			centreVis(false, -1);
	}
	// direccion de impulso
	if (key == 'w') {
		propulsar({ 1,0,0 });
	}
	if (key == 's') {
		propulsar({ -1,0,0 });
	}
	if (key == 'a') {
		propulsar({ 0,0,-1 });
	}
	if (key == 'd') {
		propulsar({ 0,0,1 });
	}
	// volver a la zona de montaje
	if (key == 'q') {
		cout << "Start" << endl;
		sceneManager->setScene(1);
	}

	switch (key)
	{
	case '0':
		SimulateTime = 1;
		break;
	case '1':
		SimulateTime = 2;
		break;
	case '2':
		SimulateTime = 8;
		break;
	case '3':
		SimulateTime = 32;
		break;
	case '4':
		SimulateTime = 256;
		break;
	case '5':
		SimulateTime = 2048;
		break;
	default:
		break;
	}

}

void ScenaLaunch::keyReleased(unsigned char key, const physx::PxTransform& camera)
{
	// deja de propulsar al levantar la tecla
	if (key == 13 || key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		if (key == 13)introPulsed = false;
		for (auto pg : partGenerators)
			pg->stopGenerate();
	}
}


void ScenaLaunch::update(double t)
{
	Scene::update(t);
	if (cabina) {
		PxVec3 globalDirection = (cabina->getActor()->getGlobalPose().q.rotate({ 0,0,-1 }));

		//cameraAnchor->setPosition((globalDirection * 100) + cabina->getPosition());
		camera->moveTo(cameraAnchor->getPosition() + Vector3(0, 0, -10));// + Vector3(cameraOffset.x, cameraOffset.y, cameraOffset.z + zoom));
		camera->lookAt(cabina->getPosition());
	}

	if (propulsando) propulsar({ 0,0,0 });

	// texto con informacion
	display_text1_position = { 10,500 };
	display_text1 = "LANZAMIENTO";
	display_text1 += "#<------------------------>";
	display_text1 += "#->Planeta Actual: ";
	display_text1 += "#->PROPULSANDO: "; propulsando ? display_text1 += "SI" : display_text1 += "NO";
	display_text1 += "#->Potencia Proulsores: " + to_string(porcentajeFuerzProp * 100) + "%";
	if (cabina) display_text1 += "#->Fuerza Aplicada: " + to_string(cabina->getActualForce().x) + "||" + to_string(cabina->getActualForce().y) + "||" + to_string(cabina->getActualForce().z);
	display_text1 += "#->Direccion Propulsion: X:" + to_string((int)DirPropulsion.x) + " Z: " + to_string((int)DirPropulsion.z);
	display_text1 += "#->Zoom: " + to_string((int)zoom);
	display_text1 += "#->Velocidad Tiempo: " + to_string(SimulateTime);

	display_text2_position = { 10,100 };
	display_text2 = "CONTROLES:";
	display_text2 += "#<------------------------>";
	display_text2 += "#->INTRO: propulsar#-I: Aumento potencia, K: Disminuye potencia#->A: Inclinacion Izquierda, D: InclinacionDerecha";

}

void ScenaLaunch::show()
{
	Scene::show();
	// resetero de propulsion
	partGenerators.clear();
	propulsando = false;

	montarCohete();
	cameraAnchor->setPosition(cabina->getPosition() + Vector3(0, 0, 100));
	fsys->addForceGenerator(new GomaModificadoGenerator(this, 10, 100, cameraAnchor, cabina));

	// setteo de la camara
	camera->setMovible(false);
	camera->moveTo({ cabina->getPosition().x, cabina->getPosition().y, cabina->getPosition().z - 100 });

	//propulsion
	for (auto pg : partGenerators)
		psys->addParticleGenerator(pg);

	// definimos la gravedad en esta escena
	gScene->setGravity({ 0,0,0 });

	// definimos el tamanio y la forma de la plataforma de lanzamiento segun el tamanio del cohete
	PlataformaLanzamiento->setShape(CreateShape(PxBoxGeometry(tamanioCohete.x + 5, 5, tamanioCohete.x + 5)), { tamanioCohete.x + 5, 5, tamanioCohete.x + 5 });
}
