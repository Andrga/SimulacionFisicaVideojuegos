#include "Cohete.h"
#include "../../basics/Scene.h"
#include "../../systems/ParticleSystem.h"
#include "../../systems/ForceSystem.h"

Spaceship::Spaceship(Scene* scn, ParticleSystem* psistm, ForceSystem* forcstm, PxPhysics* gPhysx, PxScene* gScn) :scene(scn), psys(psistm), fsys(forcstm), gScene(gScn), gPhysics(gPhysx)
{
	cabina = new Modulo("Cabina", scene, gPhysics, gScene, CoheteInfo->tipo, nullptr);
	POS_INI_CABINA_LAUNCH.y = RADIO_PLANETA_TIERRA + tamanioCohete.y + 5;
	cabina->setPosition(POS_INI_CABINA_LAUNCH);

	montarCoheteRec(CoheteInfo, cabina, gPhysics, gScene);
	scene->addGameObject(cabina);

	//propulsion
	for (int i = 0; i < partGenerators.size(); i++)
	{
		psys->addParticleGenerator(partGenerators[i]);
	}


}

Spaceship::~Spaceship()
{
}

void Spaceship::startParticles()
{
	for (int i = 0; i < partGenerators.size(); i++)
	{
		partGenerators[i]->startGenerate();
	}
}

void Spaceship::stopParticles()
{
	for (int i = 0; i < partGenerators.size(); i++)
	{
		partGenerators[i]->stopGenerate();
	}
}

void Spaceship::useParachute()
{
	paracaActivo ?
		stopParachute() :
		startParachute();
}

void Spaceship::explote()
{
	if (explotado) return;
	explotado = true;
	combustible = 0;

	psys->addParticleGenerator(new ExplosionParticleGen(cabina->getPosition(), 100, psys, scene, gPhysics, gScene));


	for (auto fj : fixedjoints)
		fj->release();
	fixedjoints.clear();
}

void Spaceship::startParachute()
{
	float mass = 1;
	float radius = sizeModule;

	parachute = new RBDynamic("widParachute", scene, gPhysics, gScene);
	scene->addGameObject(parachute);
	parachute->setShape(CreateShape(PxSphereGeometry(radius)), { radius, radius , radius });
	((PxRigidDynamic*)parachute->getActor())->setLinearDamping(0.1);

	Vector3 cabinapos = cabina->getPosition();

	PxVec3 globalDirection = cabina->getRotation().rotate({ 0,1,0 });
	parachute->setPosition(Vector3(cabinapos.x, cabinapos.y, cabinapos.z) + globalDirection * 100);
	parachute->setMass(mass);
	parachute->setDensity(0.15);



	// formula esfera hueca
	float I = (2 * mass * (radius * radius)) / 3;
	((PxRigidDynamic*)parachute->getActor())->setMassSpaceInertiaTensor({ I, I, I });

	forcGenParac = new GomaModificadoGenerator(scene, TENSION_ENTRE_MODULOS, tamanioCohete.y, cabina, parachute);
	fsys->addForceGenerator(forcGenParac);
	paracaActivo = true;
}

void Spaceship::stopParachute()
{
	fsys->eraseForceGenerator(forcGenParac);
	parachute->setAlive(false);

	paracaActivo = false;
}

void Spaceship::propulsar(Vector3 dir)
{
	if (combustible <= 0)
	{
		cout << "NO COMBUSTIBLE" << endl;
		stopParticles();
		return;
	}
	else
	{
		combustible -= 0.01 * porcentajeFuerzProp;
	}

	DirPropulsion = dir;

	startParticles();

	for (auto o : Propulsores) {
		// si o no es un modulo de cohete, ni un propulsor lo salta
		if (o->getName().substr(0, 3) == "mod" && o->getTipo() == PROPULSOR) {
			// setting de la direccion en la que propulsar
			PxVec3 globalDirection = o->getRotation().rotate({ 0,1,0 });

			// si hay rotacion por input se aniade rotacion adicional
			if (dir.x != 0 || dir.z != 0)
			{
				PxQuat aditionalRotation(PxPi * 30 / 180, dir);
				globalDirection = aditionalRotation.rotate(globalDirection);

			}

			o->addForce(globalDirection * (FUERZA_PROPULSOR * porcentajeFuerzProp));
		}
	}
}

Modulo* Spaceship::montarCoheteRec(ModuloInfo* modulo, Modulo* actualMod, PxPhysics* gPhysics, PxScene* gScene)
{
	// si no hay modulo info entonces no puede crear modulo
	if (modulo == nullptr) return nullptr;


	//crea los modulos colindantes	
	if (modulo->derecha != nullptr)
	{
		modulo->derecha->izquierda = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* derecha = creaModulo(modulo->derecha, actualMod, { -1,0,0 }, gPhysics, gScene);
		montarCoheteRec(modulo->derecha, derecha, gPhysics, gScene);
	}
	if (modulo->abajo != nullptr) {
		modulo->abajo->arriba = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* abajo = creaModulo(modulo->abajo, actualMod, { 0,-1,0 }, gPhysics, gScene);
		montarCoheteRec(modulo->abajo, abajo, gPhysics, gScene);
	}
	if (modulo->izquierda != nullptr) {
		modulo->izquierda->derecha = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* izquierda = creaModulo(modulo->izquierda, actualMod, { 1,0,0 }, gPhysics, gScene);
		montarCoheteRec(modulo->izquierda, izquierda, gPhysics, gScene);
	}
	if (modulo->arriba != nullptr) {
		modulo->arriba->abajo = nullptr; // eliminamos la referencia al modulo cabina para que no lo cree nuevamente en el metodo recursivo
		Modulo* arriba = creaModulo(modulo->arriba, actualMod, { 0,1,0 }, gPhysics, gScene);
		montarCoheteRec(modulo->derecha, arriba, gPhysics, gScene);
	}

	return actualMod;
}

Modulo* Spaceship::creaModulo(ModuloInfo* modulo, Modulo* actualMod, Vector3 dir, PxPhysics* gPhysics, PxScene* gScene)
{
	Modulo* mod = new Modulo("nuevo", scene, gPhysics, gScene, modulo->tipo, cabina);
	mod->setPosition(actualMod->getPosition() + (dir * sizeModule));

	// unimos los modulos por fixedJoints
	PxFixedJoint* fixedJoint = PxFixedJointCreate(*gPhysics,
		actualMod->getActor(), PxTransform(PxVec3(0.0f, 0.0f, 0.0f)),
		mod->getActor(), PxTransform(-dir * sizeModule));
	// setteamos una fuerza maxima a partir de la cual se rompen separan los constrains
	fixedJoint->setBreakForce(FUERZA_PROPULSOR * 500, FUERZA_PROPULSOR * 500);
	// aniado los joints a la lista para eliminarlos en caso de explosion
	fixedjoints.push_back(fixedJoint);

	Vector3 posrel = dir * sizeModule;
	cout << posrel.x << "//" << posrel.y << "//" << posrel.z << endl;
	cout << mod->getPosition().x << "//" << mod->getPosition().y << "//" << mod->getPosition().z << endl;
	// aniade el gameobject
	scene->addGameObject(mod);

	// si es un propulsor aniadimos sistema de particulas para la propulsion
	if (modulo->tipo == PROPULSOR) {
		partGenerators.push_back(new PropulsionParticleGen(mod->getPosition(), 10, psys, scene, gPhysics, gScene, &porcentajeFuerzProp, mod));
		Propulsores.push_back(mod);
	}
	else if (modulo->tipo == TANQUE) {
		combustible += 100;
	}

	return mod;
}