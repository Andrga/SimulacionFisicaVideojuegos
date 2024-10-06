#pragma once
#include "Particle.h"
class Proyectile :    public Particle
{
private: 
	Vector3 gravity;
	float mass;
public:
	Proyectile(Vector3 Pos = Vector3(0,0,0), Vector3 Vel = Vector3(0,0,0), Vector3 Acc = Vector3(0,0,0),
		Vector3 grav= Vector3(0,-9,8), float Dmp = 1, float mas = 1);
	~Proyectile() {};


	bool update(double t) override;

};

