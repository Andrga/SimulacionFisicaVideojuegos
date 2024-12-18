#pragma once
#include <vector>
#include <algorithm>
#include "../basics/System.h"
#include "ForceGenerator.h"

using namespace std;

class ForceSystem : public System
{
private:
	vector<ForceGenerator*> forceGenerators;
	vector<ForceGenerator*> eliminableForceGenerators;
public:
	ForceSystem(Scene* scn);
	~ForceSystem();

	void affectParticles(unordered_map<string, GameObjectInfo>const& gameObjects, double t) override;

	void addForceGenerator(ForceGenerator* forcGen);
	void eraseForceGenerator(ForceGenerator* forcGen);
};

