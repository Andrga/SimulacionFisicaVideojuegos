#pragma once
#include "../basics/Particle.h"
#include "../basics/Widget.h"

class Scene;

class ForceGenerator
{
protected:
	// Propiedades inicio
	float radious = 0;
	Vector3 origen = { 0,0,0 };
	// Representacion de la zona de afectacion
	Widget* widget = nullptr;
	Scene* scene = nullptr;

	void generateRadiousSphere();

public:
	ForceGenerator(Vector3 org, Scene* scn);
	virtual~ForceGenerator() = 0;


	virtual Vector3 generateForce(Particle& particle) = 0;
	bool onRadious(Vector3 Pos);

	virtual void update(double delta) {};

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
	VientoGenerador(Vector3 org, Scene* scn, Vector3 vVel = { 0,0,0 }) :ForceGenerator(org, scn), vientoVel(vVel) {};
	~VientoGenerador() {};

	void update(double delta) {}

	Vector3 generateForce(Particle& particle) override;
};

class TorvellinoGenerator : public ForceGenerator
{
protected:
	//coheficiente de rozamiento
	float k = 1;
public:
	TorvellinoGenerator(Vector3 org, Scene* scn) :ForceGenerator(org, scn) {};
	~TorvellinoGenerator() {};

	void update(double delta) {}

	Vector3 generateForce(Particle& particle) override;
};

class ExplosionGenerator : public ForceGenerator
{
protected:
	//potencia de la explosion
	float k = 100;
	float tau = 1;
	float simuleTime = 0;
	float startSimuleTime = 0;
public:
	ExplosionGenerator(Vector3 org, Scene* scn) :ForceGenerator(org, scn) { simuleTime = 0; };
	~ExplosionGenerator() {};

	// Settea la potencia de la explosion
	void setPotencia(float p) { k = p; };
	void startGenerate() {
		simuleTime = 0;
	};

	void update(double delta) { 
		simuleTime += delta; }

	Vector3 generateForce(Particle& particle) override;
};