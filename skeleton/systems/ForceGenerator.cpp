#include "ForceGenerator.h"
#include "../basics/Scene.h"
#include "../ProyectoFinal/ObjetorsDeJuego/Modulo.h"

#include <cmath>

void ForceGenerator::generateRadiousSphere()
{
	if (radius <= 0)
		return;
	// si ya existe un render item, elimina el que esta y crea uno nuevo con el nuevo radio
	if (!widget)
	{
		widget = new Widget("widRadioSphera", scene, origen, radius);

		scene->addGameObject(widget);
	}

	widget->setShape(CreateShape(physx::PxSphereGeometry(radius)));
}

ForceGenerator::ForceGenerator(Vector3 org, Scene* scn) : origen(org), scene(scn)
{
	generateRadiousSphere();
}

ForceGenerator::~ForceGenerator()
{
}

bool ForceGenerator::onRadious(GameObject* obj)
{
	if (obj == nullptr) return false;
	if (radius == 0)
		return true;
	return (obj->getPosition() - origen).magnitude() <= radius;
}

void ForceGenerator::setRadious(float rad)
{
	radius = rad;
	generateRadiousSphere();
}
// ------- GENERADOR DE GRAVEDAD --------
Vector3 GravityGenerator::generateForce(GameObject& obj)
{
	return gravity * obj.getMass();
}


// ------- GENERADOR DE VIENTO --------
Vector3 VientoGenerador::generateForce(GameObject& obj)
{
	Vector3 force(0, 0, 0);
	// calculo de la fuerza en un viento no turbulento
	force = k1 * (vientoVel - obj.getVelocity()) + k2;

	return force;
}

// ------- GENERADOR DE TORVELLINO -------
Vector3 TorbellinoGenerator::generateForce(GameObject& obj)
{
	Vector3 force(0, 0, 0),
		partPos = obj.getPosition();

	//calculo de la fuerza en torvellino
	force = k * Vector3(-(partPos.z - origen.z), 50 - (partPos.y - origen.y), partPos.x - origen.x);

	force -= obj.getVelocity();

	return force;
}

// -------- GENERADOR DE EXPLOSION --------
Vector3 ExplosionGenerator::generateForce(GameObject& obj)
{
	Vector3 force(0, 0, 0);
	simuleTime;

	if (simuleTime < 0 || simuleTime >= 4 * tau) return force;


	// distancia al centro de la explosion
	float r = (obj.getPosition() - origen).magnitude();
	// si la distancia es menor que el radio la fuerza es 0
	if (r >= radius) return force; // creo que esto no hace falta, porque si entra al metodo es porque r<radious

	force = ((k / r * r) * (obj.getPosition() - origen)) * exp(-simuleTime / tau);



	return force;
}

// ------- MUELLES -------
Vector3 SpringGenerator::generateForce(GameObject& obj)
{
	Vector3 force{ 0,0,0 };

	// largura actual del muelle
	Vector3 dir = origen - obj.getPosition();
	float actuallenth = dir.magnitude();
	dir.normalize();

	// deformacion del muelle
	float difflenth = actuallenth - restingLength;

	// calculo de la fuerza
	force = dir * k * difflenth;

	//cout << force.y << endl;
	return force;
}

// ------ GOMA ELASTICA ------
Vector3 GomaGenerator::generateForce(GameObject& obj)
{
	Vector3 position1 = object1->getPosition();
	Vector3 force{ 0,0,0 };

	// largura actual del muelle
	Vector3 dir = position1 - obj.getPosition();
	float actuallenth = dir.magnitude();
	dir.normalize();

	// deformacion del muelle
	float difflenth = actuallenth - restingLength;
	if (difflenth <= 0) difflenth = 0;
	// calculo de la fuerza
	force = dir * k * difflenth;

	// aplica la fueza a ambos extremos del muelle
	object1->addForce(-force);
	return force;
}

// ------ FLOTACION -----
Vector3 FlotationGenerator::generateForce(GameObject& particle)
{
	float height = particle.getSize().y * 2,
		h = particle.getPosition().y,
		h0 = origen.y,
		immersed = 0,
		liquidDensity = k,
		volume = pow(particle.getSize().y * 2, 3);

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
	return force;
}
// goma elastica modificada con amortiguacion para unir con paracaidas
Vector3 GomaModificadoGenerator::generateForce(GameObject& obj)
{
	if (!object1->getAlive() || !obj.getAlive()) return{ 0,0,0 };

	Vector3 positionCabina = object1->getPosition();
	Vector3 PositionCamara = obj.getPosition();
	Vector3 force{ 0,0,0 };

	// largura actual del muelle
	Vector3 dir = positionCabina - PositionCamara;
	float actuallenth = dir.magnitude();
	dir.normalize();

	// deformacion del muelle
	float difflenth = actuallenth - restingLength;

	// calculo de la fuerza
	force = dir * k * difflenth;

	// amortiguacion a la fuerza segun la velocidad
	Vector3 velRelativa = object1->getVelocity() - obj.getVelocity();
	Vector3 amortiguadoForce = velRelativa * 0.5; // velocidad * amortiguacion

	// aplica la fueza a ambos extremos del muelle
	//object1->addForce(-force);
	return force + amortiguadoForce;
}

void GravedadPlanetaGenerator::generateRadiousSphere()
{
	if (radius <= 0)
		return;
	// si ya existe un render item, elimina el que esta y crea uno nuevo con el nuevo radio
	if (!widget)
	{
		widget = new Widget("radPlt" + planetName, scene, poseOrg, radius); // el nombre de los widgets que representan la gravedad de un planeta comienza por "widplt"

		scene->addGameObject(widget);
	}

	widget->setShape(CreateShape(physx::PxSphereGeometry(radius)), { radius ,radius ,radius });
}

// GRAVEDAD PLANETARIA
Vector3 GravedadPlanetaGenerator::generateForce(GameObject& object)
{
	float distanciaCentro = (object.getPosition() - poseOrg->p).magnitude();
	// porcentaje de gravedad que afecta al objeto (cuanto mas lejos del planeta menos le afecta
	float gravedadAplicada;

	// calculo de porcentaje de gravedad que se aplica
	if (distanciaCentro <= radioPlaneta)
		gravedadAplicada = 1;
	else if (distanciaCentro >= radius)
		gravedadAplicada = 0;
	else
		gravedadAplicada = (radius - distanciaCentro) / (radius - radioPlaneta);

	// aplicamos la gravedad base
	gravedadAplicada *= gravedad;

	// calculo de la direccion a la que aplicar la fuerza (hacia el centro del planeta)
	Vector3 dir = object.getPosition() - poseOrg->p;
	dir.normalize();

	//cout << object.getName() << " GRAVEDAD ACTUAL: " << gravedadAplicada << endl;

	return dir * gravedadAplicada * object.getMass();
}

// genera fuerza de arrastre segun el fluido
Vector3 FuerzaArrastreGenerator::generateForce(GameObject& object)
{
	Vector3 force = { 0,0,0 };

	float distanceToCentre = (object.getPosition() - poseOrg->p).magnitude();
	float rocApplied;

	// calculo de porcentaje de gravedad que se aplica
	if (distanceToCentre <= radioPlaneta)
		rocApplied = 1;
	else if (distanceToCentre >= radius)
		rocApplied = 0;
	else
		rocApplied = (radius - distanceToCentre) / (radius - radioPlaneta);

	// calculo de la fuerza
	force = ((cohefficient / radius * radius) * (object.getPosition() - poseOrg->p)) * rocApplied;

	return force;
}
