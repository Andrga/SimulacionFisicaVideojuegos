#include "DockSystem.h"

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
		if (!docks[i].Particle1->getAlive() && !docks[i].Particle2->getAlive()) {
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
	// si una de las dos particulas es nula no se genera fuerza
	if (!dock.Particle1->getAlive() || !dock.Particle2->getAlive())
		return;

	Vector3 force{ 0,0,0 };
	float k = dock.k, restLenth = dock.resting_length;

	// largura actual del muelle
	Vector3 dir = dock.Particle1->getPose().p - dock.Particle2->getPose().p;
	float actualLenth = dir.magnitude();
	dir.normalize();

	// deformacion del muelle
	//float difflenth = actualLenth - restLenth;

	// Cálculo de la deformación (solo positiva)
	float difflenth = max(0.0f, actualLenth - restLenth);  // Solo fuerza si se estira

	// calculo de la fuerza
	force = dir * k * difflenth;

	// aplica la fueza a ambos extremos del muelle
	dock.Particle2->addForce(force);
	dock.Particle1->addForce(-force);
}
