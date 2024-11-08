#pragma once
#include <vector>
#include "Particle.h"

using namespace std;

class ForceGenerator;

class ForceSystem : public Object
{
private:
	vector<ForceGenerator*> forceGenerators;
public:
	ForceSystem();
	~ForceSystem();

	bool update(double t) override;

	void addForceGenerator(ForceGenerator* forcGen);
};

