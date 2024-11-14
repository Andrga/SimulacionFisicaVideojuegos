#pragma once
#include <vector>
#include "../basics/System.h"
#include "ForceGenerator.h"

using namespace std;

class ForceSystem : public System
{
private:
	vector<ForceGenerator*> forceGenerators;
public:
	ForceSystem();
	~ForceSystem();

	void affectParticles(vector<Particle*>& particles, double t) override;

	void addForceGenerator(ForceGenerator* forcGen);
};

