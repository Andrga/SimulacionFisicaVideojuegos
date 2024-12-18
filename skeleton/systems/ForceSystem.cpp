#include "ForceSystem.h"
#include "ForceGenerator.h"

ForceSystem::ForceSystem(Scene* scn) : System(scn)
{
}

ForceSystem::~ForceSystem()
{
}

void ForceSystem::affectParticles(unordered_map<string, GameObjectInfo>const& gameObjects, double t)
{
	for (auto p : gameObjects) {
		for (auto g : forceGenerators) {
			if (g != nullptr && g->onRadious(p.second.gameObject))
			{
				p.second.gameObject->addForce(g->generateForce(*p.second.gameObject));
			}
		}
	}

	for (auto g : forceGenerators)
	{
		g->update(t);
	}

	for (int i = 0; i < eliminableForceGenerators.size(); i++)
	{
		auto it = find(forceGenerators.begin(), forceGenerators.end(), eliminableForceGenerators[i]);
		if (it != forceGenerators.end()) {
			forceGenerators.erase(it);
			i--;
		}
	}
}


void ForceSystem::addForceGenerator(ForceGenerator* forcGen)
{
	forceGenerators.push_back(forcGen);
}

void ForceSystem::eraseForceGenerator(ForceGenerator* forcGen)
{
	eliminableForceGenerators.push_back(forcGen);
}
