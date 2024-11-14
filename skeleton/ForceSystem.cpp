#include "ForceSystem.h"
#include "ForceGenerator.h"

ForceSystem::ForceSystem() : System()
{}

ForceSystem::~ForceSystem()
{
}

void ForceSystem::affectParticles(vector<Particle*>& particles)
{
	for (auto p : particles) {
		for (auto g : forceGenerators) {
			if (g->onRadious(p->getPose().p))
			{
				p->addForce(g->generateForce(p->getPose().p, p->getVelocity()));
			}
		}
	}
}


void ForceSystem::addForceGenerator(ForceGenerator* forcGen)
{
	forceGenerators.push_back(forcGen);
}
