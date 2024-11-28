#include "DockSystem.h"
#include "../basics/Scene.h"

Dock DockSystem::findDock(Particle* part)
{
	Dock dock;

	for (auto d : docks) {
		if (d.Particle1 == part || d.Particle2 == part) {
			dock = d;
			break;
		}
	}
	return dock;
}

bool DockSystem::update(double t)
{
	for (int i = 0; i < docks.size(); i++) {
		// si una de las dos particulas no esta viva elimina el muelle
		if ((docks[i].Particle1 != nullptr && !docks[i].Particle1->getAlive()) || !docks[i].Particle2->getAlive()) {
			docks.erase(docks.begin() + i);
			i--;
		}
		else
			generateForce(docks[i]);
	}

	return false;
}

void DockSystem::generateForce(Dock& dock)
{
	Vector3 position1;
	if (dock.Particle1 != nullptr)
		position1 = dock.Particle1->getPose().p;
	else
		position1 = dock.anchor;


	Vector3 force{ 0,0,0 };
	float k = dock.k, restLenth = dock.resting_length;

	// largura actual del muelle
	Vector3 dir = position1 - dock.Particle2->getPose().p;
	float actuallenth = dir.magnitude();
	dir.normalize();

	// deformacion del muelle
	float difflenth = actuallenth - restLenth;

	// calculo de la fuerza
	force = dir * k * difflenth;

	// aplica la fueza a ambos extremos del muelle
	if (dock.Particle1)
		dock.Particle1->addForce(-force);
	dock.Particle2->addForce(force);
}


void FloatationSystem::generateForce(Dock& dock)
{
	float height = 1.0,
		h = dock.Particle2->getPose().p.y- height,
		h0 = dock.anchor.y -height,
		immersed = 0,
		liquidDensity = dock.k,
		volume = pow(dock.Particle2->getSize() * 2, 3);

	if (h - h0 > height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > height * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / height + 0.5;
	}


	Vector3 force{ 0,0,0 };


	// calculo de la fuerza
	force.y = liquidDensity * volume * immersed * 9.8;

	// aplica la fueza a ambos extremos del muelle
	dock.Particle2->addForce(force);
}

void FloatationSystem::addDockFlot(float h, Particle* obj2, float k)
{
	docks.push_back({ {0,h,0}, nullptr, obj2, k, 0 });
	//Widget* superficie = new Widget({ 0,100,0 }, CreateShape(physx::PxBoxGeometry(5, 0.2, 5)));
	//scene->addObject(superficie);
	//superficieWdgt.push_back(superficie);
}
