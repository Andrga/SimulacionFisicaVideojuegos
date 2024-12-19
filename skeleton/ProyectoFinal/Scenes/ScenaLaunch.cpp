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


	// creacion de los planetas
	planetas.push_back(new Planeta(this, gPhysics, gScene, 0, fsys, 0)); // tierra
	planetas.push_back(new Planeta(this, gPhysics, gScene, 1, fsys, 0.05)); // luna
	planetas.push_back(new Planeta(this, gPhysics, gScene, 2, fsys, 0.1)); // marte
	planetas.push_back(new Planeta(this, gPhysics, gScene, 3, fsys, 0.01)); // venus

	// plataforma de lanzamiento del cohete
	PlataformaLanzamiento = new RBStatic("PlataformaLanzamiento", this, gPhysics, gScene);
	PlataformaLanzamiento->setPosition({ POS_INI_CABINA_LAUNCH.x ,RADIO_PLANETA_TIERRA + 5, POS_INI_CABINA_LAUNCH.z });
	PlataformaLanzamiento->setShape(CreateShape(PxBoxGeometry(tamanioCohete.x + 5, 5, tamanioCohete.x + 5)), { tamanioCohete.x + 5, 5, tamanioCohete.x + 5 });
	PlataformaLanzamiento->setColor({ 1,1,1,1 });
	addGameObject(PlataformaLanzamiento);

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
		if (spaceship->getPorcPropulsion() < 1) spaceship->setPorcPropulsion(spaceship->getPorcPropulsion() + 0.01);
		else spaceship->setPorcPropulsion(1);
	}
	if (key == 'k') {
		if (spaceship->getPorcPropulsion() > 0) spaceship->setPorcPropulsion(spaceship->getPorcPropulsion() - 0.01);
		else spaceship->setPorcPropulsion(0);
	}
	// zoom
	if (key == 'o') {
		zoomFactor++;
		zoom = zoomFactor * zoomVel;
	}
	if (key == 'l') {
		zoomFactor--;
		zoom = zoomFactor * zoomVel;
	}
	if (key == '.') {
		zoomFactor = 0;
		zoom = 0;
	}
	// direccion de impulso
	if (key == 'w') {
		spaceship->propulsar({ 1,0,0 });
	}
	if (key == 's') {
		spaceship->propulsar({ -1,0,0 });
	}
	if (key == 'a') {
		spaceship->propulsar({ 0,0,-1 });
	}
	if (key == 'd') {
		spaceship->propulsar({ 0,0,1 });
	}
	// activa parcaidas
	if (key == 'm') {
		spaceship->useParachute();
		cout << "PARACAIDAS" << endl;
	}
	// volver a la zona de montaje
	if (key == 'q') {
		cout << "Start" << endl;
		sceneManager->setScene(1);
	}

	// velocidad de simulacion 
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
		spaceship->stopParticles();
	}
}


void ScenaLaunch::update(double t)
{
	// si no hay cohete cuelve a la escena anterior
	if (!spaceship)
		return;

	for (auto p : planetas)
		p->update(t);

	PxVec3 globalDirection = (spaceship->getRotation().rotate({ 0,0,-1 }));

	camera->moveTo(spaceship->getPosition() + Vector3(0, 0, 100 + zoom));
	camera->lookAt(spaceship->getPosition());


	if (propulsando) spaceship->propulsar({ 0,0,0 });

	// texto con informacion
	display_text1_position = { 10,500 };
	display_text1 = "LANZAMIENTO";
	display_text1 += "#<------------------------>";
	display_text1 += "#->Ultimo planeta: " + spaceship->getPlanet();
	display_text1 += "#->PROPULSANDO: "; propulsando ? display_text1 += "SI" : display_text1 += "NO";
	display_text1 += "#->Potencia Proulsores: " + to_string(spaceship->getPorcPropulsion() * 100) + "%";
	display_text1 += "#->Combustible: " + to_string(spaceship->getCombustible());
	mostrarDirCohete(spaceship->getDirection());
	display_text1 += "#->Zoom: " + to_string((int)zoom);
	display_text1 += "#->Velocidad Tiempo: " + to_string(SimulateTime);

	display_text2_position = { 10,100 };
	display_text2 = "CONTROLES:";
	display_text2 += "#<------------------------>";
	display_text2 += "#->INTRO: Propulsar->A: Inclinacion Izquierda, D: Inclinacion Derecha, W: Inclinacion Frente, D: Inclinacion Atras#-I: Aumento Potencia, K: Disminuye Potencia";
	display_text2 += "#->O: Zoom Positivo, L: Zoom Negativo, . : Resetea Zoom#->Q: Vuelve A Montaje, M: Activa Paracaidas";
	display_text2 += "#->0: velocidad tiempo = 1, 1: velocidad tiempo  = 2, 2 : velocidad tiempo  = 8";

	Scene::update(t);
}

void ScenaLaunch::mostrarDirCohete(Vector3 dir)
{
	// trunca los parametros a 2 decimales
	int x = (int)(dir.x * 100);
	int y = (int)(dir.y * 100);
	int z = (int)(dir.z * 100);
	// direccion a traves de los ejes
	display_text1 += "#->Direccion re`pecto a la vertical:#";
	display_text1 += "  X: "; display_text1 += (dir.x >= 0 ? ">" : "<"); display_text1 += " ("; display_text1 += to_string(abs(x / 100)) + ","; display_text1 += to_string(abs(x % 100)); display_text1 += ")#";
	display_text1 += "  Y: "; display_text1 += (dir.y >= 0 ? "^" : "v"); display_text1 += " ("; display_text1 += to_string(abs(y / 100)) + ","; display_text1 += to_string(abs(y % 100)); display_text1 += ")#";
	display_text1 += "  Z: "; display_text1 += (dir.z >= 0 ? "o" : "x"); display_text1 += " ("; display_text1 += to_string(abs(z / 100)) + ","; display_text1 += to_string(abs(z % 100)); display_text1 += ")";
}

void ScenaLaunch::show()
{
	Scene::show();
	propulsando = false;


	spaceship = new Spaceship(this, psys, fsys, gPhysics, gScene);

	// setteo de la camara
	camera->setMovible(false);
	camera->moveTo({ spaceship->getPosition().x, spaceship->getPosition().y, spaceship->getPosition().z - 100 });

	// definimos la gravedad en esta escena
	gScene->setGravity({ 0,0,0 });

	// definimos el tamanio y la forma de la plataforma de lanzamiento segun el tamanio del cohete
	PlataformaLanzamiento->setShape(CreateShape(PxBoxGeometry(tamanioCohete.x + 5, 5, tamanioCohete.x + 5)), { tamanioCohete.x + 5, 5, tamanioCohete.x + 5 });
}

void ScenaLaunch::exploteSpaceship()
{
	spaceship->explote();
}
