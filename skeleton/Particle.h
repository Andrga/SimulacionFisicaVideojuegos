#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "iostream"
#include "Object.h"

using namespace std;

class Particle : public Object
{
public:
	// constructoras:
	Particle(const Particle& other);
	Particle(Vector3 Pos = { 0,0,0 }, Vector3 Vel = { 0,0,0 }, float siz = 3);
	Particle(Vector3 Pos = { 0,0,0 }, Vector3 Vel = { 0,0,0 }, float siz = 3, float mas = 1);
	//Particle(Vector3 Pos = { 0,0,0 }, Vector3 Vel = { 0,0,0 }, Vector3 Acc = { 0,0,0 }, float Dmp = 1, float siz = 3, float lifet = 2);
	Particle(Vector3 Pos = { 0,0,0 }, Vector3 Vel = { 0,0,0 }, Vector3 Acc = { 0,0,0 }, float Dmp = 1, float siz = 3, float lifet = 2, float mass = 1);
	~Particle();

	// metodos de actualizacion:
	void integrate(double t);
	// Metodo que actualiza la particula( Return "TRUE" Viva || "FALSE" A eliminar)
	bool update(double t) override;

	//void setRotation(Vector3 pos);

	// getters:
	physx::PxTransform getPose() { return pose; }
	Vector3 getVelocity() { return velocity; }
	Vector3 getAcceleration() { return acceleration; }
	float getSize() { return size; }
	float getLifeTime() const { return lifeTime; }
	float getStartLifeTime() { return startlifeTime; }

	// setters:
	void setPosition(Vector3 pos);
	void setStartLifeTime(float life) { startlifeTime = life; }
	void setColor(Vector4 color) { renderItem->color = color; }
	void setMass(float mas) { mass = mas; }

	// fuerzas:
	void addForce(float x, float y, float z) { forces.push_back(Vector3(x, y, z)); }
	void addForce(Vector3 force) { forces.push_back(force); }
	void applyForce();

protected:
	// propiedades fisicas de la particula
	float size = 3;
	float mass = 1;
	physx::PxTransform pose;
	vector<Vector3> forces;

	// propiedades del movimiento e la particula
	bool eulerSemiimplicito = true;
	Vector3 velocity;
	Vector3 acceleration;
	float damping;

	// propiedades de vida por tiempo de la particula
	float lifeTime = 0;
	float startlifeTime = 10;

	RenderItem* renderItem;
};

