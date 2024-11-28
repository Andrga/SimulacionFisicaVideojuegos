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
	virtual bool onRadious(Particle* part);

	virtual void update(double delta) {};

	void setRadious(float rad);
};

// ------- GENERADOR DE GRAVEDAD --------
class GravityGenerator : public ForceGenerator {
protected:
	//aceleracion de la gravedad
	Vector3 gravity = { 0,-9.8,0 };
public:
	GravityGenerator(Vector3 org, Scene* scn, Vector3 grav) :ForceGenerator(org, scn), gravity(grav) {};
	~GravityGenerator() {};

	void update(double delta) {}

	Vector3 generateForce(Particle& particle) override;
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

class TorbellinoGenerator : public ForceGenerator
{
protected:
	//coheficiente de rozamiento
	float k = 1;
public:
	TorbellinoGenerator(Vector3 org, Scene* scn) :ForceGenerator(org, scn) {};
	~TorbellinoGenerator() {};

	void update(double delta) {}

	Vector3 generateForce(Particle& particle) override;
};

class ExplosionGenerator : public ForceGenerator
{
protected:
	//potencia de la explosion
	float k = 100;
	float tau = 0.05;
	float ve = 125; // velocidad de expansion de la explosion
	float simuleTime = 0;
public:
	ExplosionGenerator(Vector3 org, Scene* scn) :ForceGenerator(org, scn) { simuleTime = 0; };
	~ExplosionGenerator() {};

	// Settea la potencia de la explosion
	void setPotencia(float p) { k = p; };
	void startGenerate() {
		simuleTime = 0;
	};

	void update(double delta) {
		if (simuleTime <= 4 * tau) {
			simuleTime += delta;
			setRadious(ve * simuleTime);
		}
	}

	Vector3 generateForce(Particle& particle) override;
};

class SpringGenerator : public ForceGenerator
{
protected:
	Particle* particle1 = nullptr;
	Particle* particle2 = nullptr;

	float k;
	float restingLength;
public:
	/// <param name="org"> Ancla </param>
	/// <param name="scn"> Scene</param>
	/// <param name="K"> Constante de elasticidad</param>
	/// <param name="restLength"> Largo muelle reposo</param>
	/// <param name="part2">Particula afectada</param>
	/// <param name="part1">Particula(ancla)</param>
	SpringGenerator(Vector3 org, Scene* scn, float K, float restLength, Particle* part2, Particle* part1 = nullptr) :
		ForceGenerator(org, scn), k(K), restingLength(restLength), particle1(part1), particle2(part2) {};
	~SpringGenerator() {};

	void setK(float K) { k = K; }
	bool onRadious(Particle* part) override { return part == particle2; };

	virtual Vector3 generateForce(Particle& particle) override;

};

class GomaGenerator : public ForceGenerator
{
protected:
	Particle* particle1 = nullptr;
	Particle* particle2 = nullptr;

	float k;
	float restingLength;
public:
	/// <param name="org"> Ancla </param>
	/// <param name="scn"> Scene</param>
	/// <param name="K"> Constante de elasticidad</param>
	/// <param name="restLength"> Largo muelle reposo</param>
	/// <param name="part2">Particula afectada</param>
	/// <param name="part1">Particula(ancla)</param>
	GomaGenerator(Vector3 org, Scene* scn, float K, float restLength, Particle* part2, Particle* part1 = nullptr) :
		ForceGenerator(org, scn), k(K), restingLength(restLength), particle1(part1), particle2(part2) {};
	~GomaGenerator() {};

	bool onRadious(Particle* part) override { return part == particle2; };

	Vector3 generateForce(Particle& particle) override;

};

class FlotationGenerator : public ForceGenerator
{
protected:
	float k; // densidad del liquido

public:
	/// <param name="h"> superficie del liquido </param>
	/// <param name="scn"> Scene</param>
	/// <param name="K"> densidad del liquido</param>
	FlotationGenerator(float h, Scene* scn, float K) :
		ForceGenerator({ 0,h,0 }, scn), k(K) {};
	~FlotationGenerator() {};

	bool onRadious(Particle* part) override { return part->getPose().p.y <= origen.y; };

	Vector3 generateForce(Particle& particle) override;

	void setDamping(Particle* part);
};