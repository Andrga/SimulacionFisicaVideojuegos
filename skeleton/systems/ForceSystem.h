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
	ForceSystem(Scene* scn);
	~ForceSystem();

	void affectParticles(unordered_map<string, GameObjectInfo>const& gameObjects, double t) override;

	void addForceGenerator(ForceGenerator* forcGen);
};

