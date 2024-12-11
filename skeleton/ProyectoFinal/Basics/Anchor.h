#pragma once
#include"../../basics/Particle.h"

class Anchor : public Particle
{
protected:

public:
	Anchor(string nam, Scene* scn, Vector3 pos) : Particle("Anch" + nam, scn, pos) {};
	~Anchor() {};
};