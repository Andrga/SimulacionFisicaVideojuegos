#include "ForceSystem.h"
#include "ForceGenerator.h"

ForceSystem::ForceSystem(Scene* scn) : System(scn)
{}

ForceSystem::~ForceSystem()
{
}

void ForceSystem::affectParticles(vector<Particle*>& particles, double t)
{
	for (auto p : particles) {
		for (auto g : forceGenerators) {
			if (g->onRadious(p->getPose().p))
			{
				p->addForce(g->generateForce(*p));
			}
		}
	}
	
	for (auto g : forceGenerators)
	{
		g->update(t);
	}
}


void ForceSystem::addForceGenerator(ForceGenerator* forcGen)
{
	forceGenerators.push_back(forcGen);
}
