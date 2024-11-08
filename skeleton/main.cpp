#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Scene.h"
#include "Proyectile.h"
#include "ParticleSystem.h"
#include "Cascada.h"
#include "Niebla.h"
#include "Sangre.h"
#include "Disparo.h"

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;

Scene* scene = nullptr;

RenderItem* xRenderItem = NULL, * yRenderItem = NULL, * zRenderItem = NULL;
PxTransform x, y, z, t;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// ------ Creamos los ejes ------
	x = { 10.0,0.0,0.0 };
	y = { 0.0,10.0,0.0 };
	z = { 0.0,0.0,10.0 };
	t = { 0.0,0.0,0.0 };

	xRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &x, { 1.0, 0.0, 0.0, 1.0 });
	yRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &y, { 0.0, 1.0, 0.0, 1.0 });
	zRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &z, { 0.0, 0.0, 1.0, 1.0 });
	//zRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &t, { 1.0, 1.0, 1.0, 1.0 });


	// ------ creamos scena ------
	scene = new Scene();

	// ----- PARTICULA -----
	//scene->addParticle( new Particle({0,0,0}, {0,1,0}, {0,10,0}, 0.98));
	// ----- PROYECTIL -----
	//scene->addObject(new Proyectile({ 0,0,0 }, { 25,25,0 }));


	// ------- SISTEMAS DE PARTICULAS ------
	//ParticleSystem* partsyst = new ParticleSystem(scene);
	//scene->addObject(partsyst);


	//------ Sistema 4 ------
	// sistema de particula cascada
	//partsyst->addParticleGenerator(new Cascada(Vector3(0, 50, 0), 10000, partsyst));

	//------ Sistema 2 ------
	// sistema de particula niebla
	//partsyst->addParticleGenerator(new Niebla(Vector3(0, 0, 0), 1000, partsyst));

	// ------ Sistema 3 -----
	// sistema de particula disparo
	//partsyst->addParticleGenerator(new Disparo(Vector3(0, 10, 0), 10, partsyst));
	// sistema de particula sangre
	//partsyst->addParticleGenerator(new Sangre(Vector3(0, 10, 50), 15, partsyst));
	Particle* part = new Particle(Particle({ 0,10,0 },{0,0,0},3,10));
		scene->addObject(part);
		part->addForce({ 0,-9.8,0 });
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	// Update de la escena
	if (scene != nullptr)
		scene->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case ' ':
	{
		break;
	}
	case 'K':
		scene->addObject(new Proyectile(camera.p, camera.q.getBasisVector2() * -25, { 0,0,0 }));
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}