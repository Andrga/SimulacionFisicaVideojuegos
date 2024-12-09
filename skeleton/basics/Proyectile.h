#pragma once
#include "Particle.h"
class Proyectile : public Particle
{
public:
	Proyectile(string nam, Scene* scn, Vector3 Pos, Vector3 Vel, Vector3 siz);
	Proyectile(string nam, Scene* scn, Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp, float mas = 1, Vector3 siz = { 3,3,3 });
	~Proyectile() {};


	bool update(double t) override;

};

