#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"
#include "Object.h"

using namespace std;

class Particle: public Object
{
public:
	Particle(const Particle& other);
	Particle(Vector3 Pos = { 0,0,0 }, Vector3 Vel = { 0,0,0 }, Vector3 Acc = { 0,0,0 }, float Dmp = 1, float siz = 3, float lifet = 10);
	~Particle();

	void integrate(double t);
	// Metodo que actualiza la particula( Return "TRUE" Viva || "FALSE" A eliminar)
	bool update(double t) override;

	float getLifeTime() const { return lifeTime; }
	void setPosition(Vector3 pos);

protected:
	Vector3 velocity;
	Vector3 acceleration;
	float damping;
	float size = 3;
	float lifeTime = 0;
	float startlifeTime = 10;

	physx::PxTransform pose;
	RenderItem* renderItem;
};

