#pragma once
#include "Particle.h"
class Proyectile : public Particle
{
public:
	Proyectile(string nam, Scene* scn, Vector3 Pos = Vector3(0, 0, 0), Vector3 Vel = Vector3(0, 0, 0), float siz = 3);
	Proyectile(string nam, Scene* scn, Vector3 Pos = Vector3(0, 0, 0), Vector3 Vel = Vector3(0, 0, 0), Vector3 Acc = Vector3(0, 0, 0), float Dmp = 1, float mas = 1, float siz = 3);
	~Proyectile() {};


	bool update(double t) override;

};

