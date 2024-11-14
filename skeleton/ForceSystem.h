#pragma once
#include <vector>
#include "System.h"
#include "ForceGenerator.h"

using namespace std;

class ForceSystem : public System
{
private:
	vector<ForceGenerator*> forceGenerators;
public:
	ForceSystem();
	~ForceSystem();

	void affectParticles(vector<Particle*>& particles) override;

	void addForceGenerator(ForceGenerator* forcGen);
};

