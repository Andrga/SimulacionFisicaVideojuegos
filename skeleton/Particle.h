#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle();

	void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

