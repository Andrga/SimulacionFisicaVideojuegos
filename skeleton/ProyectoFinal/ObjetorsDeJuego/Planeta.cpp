#include "Planeta.h"
#include "../../basics/Scene.h"
#include "../../systems/ForceSystem.h"
#include "../../systems/ForceGenerator.h"

Planeta::Planeta(Scene* scn, PxPhysics* gPhysics, PxScene* gScene, int id, ForceSystem* fsys, float angle)
{
	scene = scn;
	rotAngle = angle;

	if (id == 0) {// Tierra
		RBStatic* tierra1 = new RBStatic("pltPlanetaTierra1", scene, gPhysics, gScene);
		tierra1->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
		tierra1->setColor({ 0.5,1,0.1,1 });
		scene->addGameObject(tierra1);

		RBStatic* tierra2 = new RBStatic("pltPlanetaTierra2", scene, gPhysics, gScene);
		tierra2->setPosition(tierra1->getPosition());
		tierra2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
		tierra2->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
		tierra2->setColor({ 0.1,1,0.5,1 });
		scene->addGameObject(tierra2);

		RBStatic* tierra3 = new RBStatic("pltPlanetaTierra3", scene, gPhysics, gScene);
		tierra3->setPosition(tierra1->getPosition());
		tierra3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
		tierra3->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
		tierra3->setColor({ 0.5,1,0.1,1 });
		scene->addGameObject(tierra3);

		RBStatic* tierra4 = new RBStatic("pltPlanetaTierra4", scene, gPhysics, gScene);
		tierra4->setPosition(tierra1->getPosition());
		tierra4->setRotation(PxQuat(PxPi / 2, PxVec3(1, 0, 0)));
		tierra4->setShape(CreateShape(PxSphereGeometry(RADIO_PLANETA_TIERRA)), { RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA, RADIO_PLANETA_TIERRA });
		tierra4->setColor({ 0.1,1,0.5,1 });
		scene->addGameObject(tierra4);

		planeta.push_back(tierra1);
		planeta.push_back(tierra2);
		planeta.push_back(tierra3);
		planeta.push_back(tierra4);
		// gravedad de planeta tierra
		fsys->addForceGenerator(new GravedadPlanetaGenerator(tierra1->getPose(), scene, -98, RADIO_GRAVEDAD_TIERRA, RADIO_PLANETA_TIERRA, "Tierra"));
		// rozamiento del fluido
		fsys->addForceGenerator(new FuerzaArrastreGenerator(tierra1->getPose(), scene, 0.014, RADIO_GRAVEDAD_TIERRA, RADIO_PLANETA_TIERRA, "Tierra"));

	}
	else if (id == 1) {
		RBStatic* luna1 = new RBStatic("pltLuna1", scene, gPhysics, gScene);
		luna1->setShape(CreateShape(PxSphereGeometry(RADIO_LUNA)), { RADIO_LUNA, RADIO_LUNA, RADIO_LUNA });
		luna1->setPosition(Vector3(0, DISTANCIA_TIERRA_LUNA, 0));
		luna1->setColor({ 0.9,0.8,0.5,1 });
		scene->addGameObject(luna1);

		RBStatic* luna2 = new RBStatic("pltLuna2", scene, gPhysics, gScene);
		luna2->setPosition(luna1->getPosition());
		luna2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
		luna2->setShape(CreateShape(PxSphereGeometry(RADIO_LUNA)), { RADIO_LUNA, RADIO_LUNA, RADIO_LUNA });
		luna2->setColor({ 1,0.9,0.5,1 });
		scene->addGameObject(luna2);

		RBStatic* luna3 = new RBStatic("pltLuna3", scene, gPhysics, gScene);
		luna3->setPosition(luna1->getPosition());
		luna3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
		luna3->setShape(CreateShape(PxSphereGeometry(RADIO_LUNA)), { RADIO_LUNA, RADIO_LUNA, RADIO_LUNA });
		luna3->setColor({ 0.9,0.8,0.5,1 });
		scene->addGameObject(luna3);

		RBStatic* luna4 = new RBStatic("pltLuna4", scene, gPhysics, gScene);
		luna4->setPosition(luna1->getPosition());
		luna4->setRotation(PxQuat(PxPi / 2, PxVec3(1, 0, 0)));
		luna4->setShape(CreateShape(PxSphereGeometry(RADIO_LUNA)), { RADIO_LUNA, RADIO_LUNA, RADIO_LUNA });
		luna4->setColor({ 1,0.9,0.5,1 });
		scene->addGameObject(luna4);

		planeta.push_back(luna1);
		planeta.push_back(luna2);
		planeta.push_back(luna3);
		planeta.push_back(luna4);
		// gravedad de la luna
		fsys->addForceGenerator(new GravedadPlanetaGenerator(luna1->getPose(), scene, -80, RADIO_GRAVEDAD_LUNA, RADIO_LUNA, "Luna"));
		// rozamiento del fluido
		fsys->addForceGenerator(new FuerzaArrastreGenerator(luna1->getPose(), scene, 0.0001, RADIO_GRAVEDAD_LUNA, RADIO_LUNA, "Luna"));
	}
	else if (id == 2) {
		RBStatic* marte1 = new RBStatic("pltMarte1", scene, gPhysics, gScene);
		marte1->setShape(CreateShape(PxSphereGeometry(RADIO_MARTE)), { RADIO_MARTE, RADIO_MARTE, RADIO_MARTE });
		marte1->setPosition(Vector3(0, DISTANCIA_TIERRA_MARTE, 0));
		marte1->setColor({ 1,0.7,0.2,1 });
		scene->addGameObject(marte1);

		RBStatic* marte2 = new RBStatic("pltMarte2", scene, gPhysics, gScene);
		marte2->setPosition(marte1->getPosition());
		marte2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
		marte2->setShape(CreateShape(PxSphereGeometry(RADIO_MARTE)), { RADIO_MARTE, RADIO_MARTE, RADIO_MARTE });
		marte2->setColor({ 1,0.5,0.2,1 });
		scene->addGameObject(marte2);

		RBStatic* marte3 = new RBStatic("pltMarte3", scene, gPhysics, gScene);
		marte3->setPosition(marte1->getPosition());
		marte3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
		marte3->setShape(CreateShape(PxSphereGeometry(RADIO_MARTE)), { RADIO_MARTE, RADIO_MARTE, RADIO_MARTE });
		marte3->setColor({ 1,0.8,0.2,1 });
		scene->addGameObject(marte3);

		RBStatic* marte4 = new RBStatic("pltMarte4", scene, gPhysics, gScene);
		marte4->setPosition(marte1->getPosition());
		marte4->setRotation(PxQuat(PxPi / 2, PxVec3(1, 0, 0)));
		marte4->setShape(CreateShape(PxSphereGeometry(RADIO_MARTE)), { RADIO_MARTE, RADIO_MARTE, RADIO_MARTE });
		marte4->setColor({ 1,0.5,0.2,1 });
		scene->addGameObject(marte4);

		planeta.push_back(marte1);
		planeta.push_back(marte2);
		planeta.push_back(marte3);
		planeta.push_back(marte4);
		// gravedad de marte
		fsys->addForceGenerator(new GravedadPlanetaGenerator(marte1->getPose(), scene, -120, RADIO_GRAVEDAD_MARTE, RADIO_MARTE, "Marte"));
		// rozamiento del fluido
		fsys->addForceGenerator(new FuerzaArrastreGenerator(marte1->getPose(), scene, 0.0001, RADIO_GRAVEDAD_MARTE, RADIO_MARTE, "Marte"));
	}
	else if (id == 3) {

		RBStatic* venus1 = new RBStatic("pltVenus1", scene, gPhysics, gScene);
		venus1->setShape(CreateShape(PxSphereGeometry(RADIO_VENUS)), { RADIO_VENUS, RADIO_VENUS, RADIO_VENUS });
		venus1->setPosition(Vector3(0, -DISTANCIA_TIERRA_VENUS, 0));
		venus1->setColor({ 0.1,0.8,1,1 });
		scene->addGameObject(venus1);

		RBStatic* venus2 = new RBStatic("pltVenus2", scene, gPhysics, gScene);
		venus2->setPosition(venus1->getPosition());
		venus2->setRotation(PxQuat(PxPi / 2, PxVec3(0, 1, 0)));
		venus2->setShape(CreateShape(PxSphereGeometry(RADIO_VENUS)), { RADIO_VENUS, RADIO_VENUS, RADIO_VENUS });
		venus2->setColor({ 0.1,0.5,1,1 });
		scene->addGameObject(venus2);

		RBStatic* venus3 = new RBStatic("pltVenus3", scene, gPhysics, gScene);
		venus3->setPosition(venus1->getPosition());
		venus3->setRotation(PxQuat(PxPi / 2, PxVec3(0, 0, 1)));
		venus3->setShape(CreateShape(PxSphereGeometry(RADIO_VENUS)), { RADIO_VENUS, RADIO_VENUS, RADIO_VENUS });
		venus3->setColor({ 0.1,0.5,1,1 });
		scene->addGameObject(venus3);

		RBStatic* venus4 = new RBStatic("pltVenus4", scene, gPhysics, gScene);
		venus4->setPosition(venus1->getPosition());
		venus4->setRotation(PxQuat(PxPi / 2, PxVec3(1, 0, 0)));
		venus4->setShape(CreateShape(PxSphereGeometry(RADIO_VENUS)), { RADIO_VENUS, RADIO_VENUS, RADIO_VENUS });
		venus4->setColor({ 0.1,0.5,1,1 });
		scene->addGameObject(venus4);

		planeta.push_back(venus1);
		planeta.push_back(venus2);
		planeta.push_back(venus3);
		planeta.push_back(venus4);
		// GRAVEDAD DE LA LUNA
		fsys->addForceGenerator(new GravedadPlanetaGenerator(venus1->getPose(), scene, -90, RADIO_GRAVEDAD_VENUS, RADIO_VENUS, "Venus"));
		// rozamiento del aire
		fsys->addForceGenerator(new FuerzaArrastreGenerator(venus1->getPose(), scene, 0.0001, RADIO_GRAVEDAD_VENUS, RADIO_VENUS, "Venus"));
	}
}

Planeta::~Planeta()
{
}

void Planeta::update(double t)
{
	for (auto p:planeta)
	{
		p->setPosition(rotateZ(p->getPosition()));
	}
}

Vector3 Planeta::rotateZ(const Vector3& v) {
	float rad = rotAngle * PxPi / 180.0f;
	float cosTheta = cos(rad);
	float sinTheta = sin(rad);

	return Vector3(v.x * cosTheta - v.y * sinTheta,
		v.x * sinTheta + v.y * cosTheta,
		v.z);
}