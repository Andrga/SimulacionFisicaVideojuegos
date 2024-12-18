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

	cameraAnchor1 = new RBStatic("wid1CameraFollow", this, gPhysics, gScene);
	cameraAnchor1->setStartLifeTime(-1);
	cameraAnchor1->setShape(CreateShape(PxSphereGeometry(0.1)), { 0, 0, 0 });
	addGameObject(cameraAnchor1);

	cameraAnchor2 = new RBDynamic("wid2CameraFollow", this, gPhysics, gScene);
	cameraAnchor2->setStartLifeTime(-1);
	cameraAnchor2->setShape(CreateShape(PxSphereGeometry(0.1)), { 0, 0, 0 });
	((PxRigidDynamic*)cameraAnchor2->getActor())->setLinearDamping(0.1);
	addGameObject(cameraAnchor2);




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
	fsys->addForceGenerator(new GravedadPlanetaGenerator(PlanetaTierra->getPosition(), this, -98, RADIO_GRAVEDAD_TIERRA, RADIO_PLANETA_TIERRA));
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
	fsys->addForceGenerator(new GravedadPlanetaGenerator(Luna1->getPosition(), this, -16.2f, RADIO_GRAVEDAD_LUNA, RADIO_LUNA + 100));
#pragma endregion

	// plataforma de lanzamiento del cohete
	PlataformaLanzamiento = new RBStatic("PlataformaLanzamiento", this, gPhysics, gScene);
	PlataformaLanzamiento->setPosition({ POS_INI_CABINA_LAUNCH.x ,RADIO_PLANETA_TIERRA + 5, POS_INI_CABINA_LAUNCH.z });
	PlataformaLanzamiento->setShape(CreateShape(PxBoxGeometry(tamanioCohete.x + 5, 5, tamanioCohete.x + 5)), { tamanioCohete.x + 5, 5, tamanioCohete.x + 5 });
	PlataformaLanzamiento->setColor({ 1,1,1,1 });
	addGameObject(PlataformaLanzamiento);

	psys->addParticleGenerator(new NieblaGen(PlataformaLanzamiento->getPosition(), 10, psys, this));


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
		if (cohete->getPorcPropulsion() < 1) cohete->setPorcPropulsion(cohete->getPorcPropulsion() + 0.01);
		else cohete->setPorcPropulsion(1);
	}
	if (key == 'k') {
		if (cohete->getPorcPropulsion() > 0) cohete->setPorcPropulsion(cohete->getPorcPropulsion() - 0.01);
		else cohete->setPorcPropulsion(0);
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
		cohete->propulsar({ 1,0,0 });
	}
	if (key == 's') {
		cohete->propulsar({ -1,0,0 });
	}
	if (key == 'a') {
		cohete->propulsar({ 0,0,-1 });
	}
	if (key == 'd') {
		cohete->propulsar({ 0,0,1 });
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
		// activa el paracaidas
	case 'm':
		cohete->useParachute();
		cout << "PARACAIDAS" << endl;
		break;
		// volver a la zona de montaje
	case 'q':
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
	if (key == 13 || key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		if (key == 13)introPulsed = false;
		cohete->stopParticles();
	}
}


void ScenaLaunch::update(double t)
{
	Scene::update(t);
	// si no hay cohete no hace lo siguiente
	if (!cohete) return;

	PxVec3 globalDirection = (cohete->getRotation().rotate({ 0,0,-1 }));

	cameraAnchor1->setPosition(cohete->getPosition() + Vector3(0, 0, 100 + zoom));
	camera->moveTo(cameraAnchor2->getPosition() + Vector3(0, 0, -10));// + Vector3(cameraOffset.x, cameraOffset.y, cameraOffset.z + zoom));
	camera->lookAt(cohete->getPosition());


	if (propulsando) cohete->propulsar({ 0,0,0 });

	// texto con informacion
	display_text1_position = { 10,500 };
	display_text1 = "LANZAMIENTO";
	display_text1 += "#<------------------------>";
	display_text1 += "#->Planeta Actual: ";
	display_text1 += "#->PROPULSANDO: "; propulsando ? display_text1 += "SI" : display_text1 += "NO";
	display_text1 += "#->Potencia Proulsores: " + to_string(cohete->getPorcPropulsion() * 100) + "%";
	display_text1 += "#->Combustible: " + to_string(cohete->getCombustible());
	//if (cohete) display_text1 += "#->Fuerza Aplicada: " + to_string(cabina->getActualForce().x) + "||" + to_string(cabina->getActualForce().y) + "||" + to_string(cabina->getActualForce().z);
	//display_text1 += "#->Direccion Propulsion: X:" + to_string((int)DirPropulsion.x) + " Z: " + to_string((int)DirPropulsion.z);
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
	propulsando = false;


	cohete = new Cohete(this, psys, fsys, gPhysics, gScene);
	cameraAnchor1->setPosition(cohete->getPosition() + Vector3(0, 0, 100));
	//cameraAnchor1->setVisibility(false);
	cameraAnchor2->setPosition(cameraAnchor1->getPosition() + Vector3(0, 0, 10));
	//cameraAnchor2->setVisibility(false);
	fsys->addForceGenerator(new GomaModificadoGenerator(this, 10, 10, cameraAnchor2, cameraAnchor1));

	// setteo de la camara
	camera->setMovible(false);
	camera->moveTo({ cohete->getPosition().x, cohete->getPosition().y, cohete->getPosition().z - 100 });

	// definimos la gravedad en esta escena
	gScene->setGravity({ 0,0,0 });

	// definimos el tamanio y la forma de la plataforma de lanzamiento segun el tamanio del cohete
	PlataformaLanzamiento->setShape(CreateShape(PxBoxGeometry(tamanioCohete.x + 5, 5, tamanioCohete.x + 5)), { tamanioCohete.x + 5, 5, tamanioCohete.x + 5 });
}
