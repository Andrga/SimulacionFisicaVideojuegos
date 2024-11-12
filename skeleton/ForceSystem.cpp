#include "ForceSystem.h"
#include "ForceGenerator.h"

ForceSystem::ForceSystem(vector<Particle*>* parts): particles(parts)
{
}

ForceSystem::~ForceSystem()
{
}

bool ForceSystem::update(double t)
{
	for (auto p : (*particles)) {
		for (auto g : forceGenerators) {
			if (g->onRadious(p->getPose().p))
				p->addForce(g->generateForce(p->getPose().p, p->getVelocity()));
		}
	}
	return false;
}

void ForceSystem::addForceGenerator(ForceGenerator* forcGen)
{
	forceGenerators.push_back(forcGen);
}
