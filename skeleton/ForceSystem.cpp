#include "ForceSystem.h"
#include "ForceGenerator.h"

ForceSystem::ForceSystem()
{
}

ForceSystem::~ForceSystem()
{
}

bool ForceSystem::update(double t)
{
	for (auto g : forceGenerators) {
		g->update(t);
	}
	return false;
}

void ForceSystem::addForceGenerator(ForceGenerator* forcGen)
{
	forceGenerators.push_back(forcGen);
}
