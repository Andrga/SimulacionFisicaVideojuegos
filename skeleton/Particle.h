#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"

using namespace std;

class Particle
{
public:
	Particle(Vector3 Pos = { 0,0,0 }, Vector3 Vel = { 0,0,0 }, Vector3 Acc = { 0,0,0 }, float Dmp = 1, float siz = 3, float lifet = 10);
	~Particle();

	void integrate(double t);
	// Metodo que actualiza la particula( Return "TRUE" Viva || "FALSE" A eliminar)
	virtual bool update(double t);

	float getLifeTime() { return lifeTime; }

protected:
	bool alive;
	Vector3 velocity;
	Vector3 acceleration;
	float damping;
	float size = 3;
	float lifeTime = 0;
	float startlifeTime = 0;

	physx::PxTransform pose;
	RenderItem* renderItem;
};

