#pragma once
#include <map>
#include "../basics/System.h"
#include <algorithm>

struct Dock {

	Vector3 anchor;
	Particle* Particle1;
	Particle* Particle2;

	float k; // constante elasticidad | densidad del liquido
	float resting_length;
};

class DockSystem : public System
{
protected:
	// part1, part2, k, resting_length
	vector<Dock> docks;

	Dock findDock(Particle* part);
public:
	DockSystem(Scene* scn) :System(scn) {};
	~DockSystem() {};

	void addDock(Particle* obj1, Particle* obj2, float k, float rest_length) {
		docks.push_back({ {0,0,0}, obj1, obj2,k, rest_length });
	}
	void addDockAnch(Vector3 anch, Particle* obj2, float k, float rest_length) {
		docks.push_back({ anch, nullptr, obj2, k, rest_length });
	}
	void deRegisterDock(Particle* key);

	bool update(double t) override;
	virtual void generateForce(Dock& dock);
};

class FloatationSystem : public DockSystem {
protected:
	vector<Widget*> superficieWdgt;
public:
	FloatationSystem(Scene* scn) : DockSystem(scn) {};
	void generateForce(Dock& dock) override;


	void addDockFlot(float h, Particle* obj2, float k);
};