#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"

using namespace std;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp = 1);
	~Particle();

	void integrate(double t);
	// Metodo que actualiza la particula
	virtual void update(double t);

protected:
	bool alive;
	Vector3 velocity;
	Vector3 acceleration;
	float damping;

	physx::PxTransform pose;
	RenderItem* renderItem;
};

