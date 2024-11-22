#pragma once
#include <map>
#include "../basics/System.h"
class DockSystem : public System
{
protected:
	// part1, part2, k, resting_length
	map<Particle*, pair<Particle*, pair<float, float>>> docks;
public:
	DockSystem() {};
	~DockSystem() {};

	void addDock(Particle* obj1, Particle* obj2, float k, float rest_length) {
		docks.insert({ obj1, {obj2,{k, rest_length}}});
	}

	bool update(double t) override;
	void generateForce(Particle* obj);

};

