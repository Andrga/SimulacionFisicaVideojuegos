#pragma once
#include "Particle.h"

class ForceGenerator
{
protected:
	// Propiedades inicio
	float radious = 1;
	Vector3 origen = { 0,0,0 };
	// Representacion de la zona de afectacion
	RenderItem* renderItem = nullptr;

	void generateRadiousSphere();

public:
	ForceGenerator(Vector3 org);
	virtual~ForceGenerator() = 0;


	virtual Vector3 generateForce(Particle& particle) = 0;
	bool onRadious(Vector3 Pos);

	void setRadious(float rad);
};

class VientoGenerador : public ForceGenerator
{
protected:
	//velocidad del viento
	Vector3 vientoVel = { 0,0,0 };
	//coheficientes de rozamiento
	float k1 = 10;
	Vector3 k2 = { 0,0,0 };
public:
	VientoGenerador(Vector3 org, Vector3 vVel) :ForceGenerator(org), vientoVel(vVel) {};
	~VientoGenerador() {};

	Vector3 generateForce(Particle& particle) override;
};

//class TorvellinoGenerator : public ForceGenerator
//{
//protected:
//	//velocidad del viento
//	Vector3 vientoVel = { 0,0,0 };
//	//coheficientes de rozamiento
//	float k = 1;
//public:
//	TorvellinoGenerator(Vector3 org, Vector3 vVel) :ForceGenerator(org), vientoVel(vVel) {};
//	~TorvellinoGenerator() {};
//
//	Vector3 generateForce(Particle& particle) override;
//};