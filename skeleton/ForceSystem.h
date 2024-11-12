#pragma once
#include <vector>
#include "Particle.h"

using namespace std;

class ForceGenerator;

class ForceSystem : public Object
{
private:

	vector<ForceGenerator*> forceGenerators;

	vector<Particle*>* particles;
public:
	ForceSystem(vector<Particle*>* parts);
	~ForceSystem();

	bool update(double t) override;
	void setVisibility(bool visibility) override {}

	void addForceGenerator(ForceGenerator* forcGen);
};

