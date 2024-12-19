#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "basics/SceneManager.h"
#include <iostream>

std::string display_text1 = "This is a test";
physx::PxVec2 display_text1_position = { 0.0f, 0.0f };
std::string display_text2 = "This is a test";
physx::PxVec2 display_text2_position = { 0.0f, 0.0f };
physx::PxVec4 display_text_color = { 1.0f, 0.2f, 0.2f, 1.0f };
int display_text_lineSpacing = 15;


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

SceneManager* sceneManager = nullptr;

RenderItem* /*xRenderItem = NULL, * yRenderItem = NULL, * zRenderItem = NULL,*/  centroRI = nullptr;
PxTransform /*ejX, ejY, ejZ,*/ centroPose;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;//contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// ------ Creamos los ejes ------
	/*ejX = { 10.0,0.0,0.0 };
	ejY = { 0.0,10.0,0.0 };
	ejZ = { 0.0,0.0,10.0 };*/
	centroPose = PxTransform({ GetCamera()->getEye().x, GetCamera()->getEye().y, GetCamera()->getEye().z });

	//cout << centroPose.p.x << "/" << centroPose.p.y << "/" << centroPose.p.z << endl;
	//cout << GetCamera()->getEye().x << "/" << GetCamera()->getEye().y << "/" << GetCamera()->getEye().z << endl;
	//centroPose.p = {GetCamera()->getDir().x, GetCamera()->getDir().y, GetCamera()->getDir().z - 10};

	/*xRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &ejX, { 1.0, 0.0, 0.0, 1.0 });
	yRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &ejY, { 0.0, 1.0, 0.0, 1.0 });
	zRenderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &ejZ, { 0.0, 0.0, 1.0, 1.0 });*/
	centroRI = new RenderItem(CreateShape(PxSphereGeometry(0.05)), &centroPose, { 1.0, 1.0, 1.0, 1 });


	// ------ creamos el scene manager ------
	sceneManager = new SceneManager(gPhysics, gScene);



}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t * SimulateTime);
	gScene->fetchResults(true);


	// Update de la escena
	if (sceneManager != nullptr)
		sceneManager->update(t * SimulateTime);


	centroPose.p = GetCamera()->getEye() + (GetCamera()->getDir()*5);
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

	sceneManager->keyPressed(key, camera);
}

// Funcion llamada cuando una tecla es despulsada
void keyReleased(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	sceneManager->keyReleased(key, camera);
}

void mouseInput(int button, int state, int x, int y)
{
	sceneManager->mouseInput(button, state, x, y);
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{

	PX_UNUSED(actor1);
	PX_UNUSED(actor2);

	cout << "COLISION" << endl;
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