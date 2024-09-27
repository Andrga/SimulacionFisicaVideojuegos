#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp);
	~Particle();

	void integrate(double t);
private:
	Vector3 vel;
	Vector3 acc;
	float dmp;

	physx::PxTransform pose;
	RenderItem* renderItem;
};

