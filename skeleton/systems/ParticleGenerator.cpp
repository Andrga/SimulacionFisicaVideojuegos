#include "ParticleGenerator.h"
#include "../basics/Scene.h"
#include "../systems/ParticleSystem.h"

ParticleGenerator::ParticleGenerator(Vector3 org, int stNpart, ParticleSystem* partsys, Scene* scn) :
	origen(org), startNGameObjects(stNpart), particleSystem(partsys), scene(scn)
{
}

ParticleGenerator::~ParticleGenerator()
{
}


void ParticleGenerator::update(double t)
{
	// Genera particulas si hace falta
	if (mayGenerate()) {
		generateParticle();
	}
}

bool ParticleGenerator::mayGenerate()
{
	return nGameObjects <= startNGameObjects;
}

void ParticleGenerator::onGameObjectDeath(GameObject* p) {
	if (generatedGameObjects.find(p) != generatedGameObjects.end()) {
		generatedGameObjects.erase(p); // Eliminar del mapa
		nGameObjects--;
	}
}

void ParticleGenerator::generateParticle() {
	cout << "---Nueva particula generada del sistema---" << endl;
}

// --- GENERADOR DE CASCADA ---
void CascadaGen::generateParticle()
{
	// cantidad de particulas no generadas
	int restParticles = (startNGameObjects / 2) - nGameObjects;

	// Generamos una cantidad de particulas, cuya cantidad entra en el rango de la capacidad de particulas maxima,
	// es decir restParticles
	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::normal_distribution<double> YnormalDistribution(5, 2.0); // media|dispersion
	std::normal_distribution<double> ZnormalDistribution(10, 2.0); // media|dispersion
	std::normal_distribution<double> LFEnormalDistribution(2, 10.0); // media|dispersion
	std::normal_distribution<double> ORGnormalDistribution(origen.x, 10.0); // media|dispersion

	// origen de la nueva particula
	Vector3 origen2;
	// velocidad para la nueva particula
	Vector3 velocity;
	velocity.x = 0;
	// tiempo de vida para la nueva particula
	float lifetime;
	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++) {
		// aleatorizamos las variabes asignadas a las nuevas particulas
		origen2 = origen;
		origen2.x = ORGnormalDistribution(generator);
		velocity.y = YnormalDistribution(generator);
		velocity.z = ZnormalDistribution(generator);
		lifetime = LFEnormalDistribution(generator);

		// creamos la nueva particula
		Particle* aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2);
		aux->setVelocity(velocity);
		aux->setSize({ 0.5 ,0.5 ,0.5 });
		aux->setStartLifeTime(lifetime);
		aux->applyGravity();

		// añadimos las particulas a la lista

		generatedGameObjects[aux] = true; // Aniaadir al mapa
		scene->addGameObject(aux, this); // Aniadir a la escena y pasar referencia del generador

		//particles.push_back(aux);
		nGameObjects++;
		nGameObjectsTotal++;

	}



}


// --- GENERADOR DE NIEBLA ---
void NieblaGen::generateParticle()
{
	// cantidad de particulas no generadas
	int restParticles = (startNGameObjects / 2) - nGameObjects;

	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::uniform_int_distribution<int> posXZUniform(-20, 20); // numero de -10 a 10
	std::uniform_int_distribution<int> posYUniform(0, 40); // numero de 0 a 20

	std::normal_distribution<double> Bdistribution(10, 0.8); // numero de 0 a restParticles

	// origen de la nueva particula
	Vector3 origen2;
	// velocidad para la nueva particula
	Vector3 velocity;
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	// tiempo de vida para la nueva particula
	float lifetime;
	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++) {
		// aleatorizamos las variabes asignadas a las nuevas particulas
		origen2 = origen;
		origen2.x = posXZUniform(generator);
		origen2.y = posYUniform(generator);
		origen2.z = posXZUniform(generator);

		lifetime = Bdistribution(generator);

		// creamos la nueva particula
		Particle* aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2);
		aux->setVelocity(velocity);
		aux->setSize({ 0.25 ,0.25 ,0.25 });
		aux->setStartLifeTime(lifetime);

		// añadimos las particulas a la lista
		generatedGameObjects[aux] = true; // Aniaadir al mapa
		scene->addGameObject(aux, this); // Aniadir a la escena y pasar referencia del generador
		aux->applyGravity();
		nGameObjects++;
		nGameObjectsTotal++;

	}



}

// --- GENERADOR DE PARTICULAS DE VARIAS MASAS ---
void RandomParticleGen::generateParticle()
{

	// cantidad de particulas no generadas
	int restParticles = (startNGameObjects / 2) - nGameObjects;

	std::uniform_int_distribution<int> numPartsUniform(0, restParticles); // numero de 0 a restParticles
	std::uniform_int_distribution<int> posXZUniform(-40, 40); // numero de -40 a 40
	std::uniform_int_distribution<int> posYUniform(0, 80); // numero de 0 a 80

	std::uniform_real_distribution<double> lifeTimeUdistribution(5, 10); // numero de 0 a restParticles
	std::normal_distribution<double> massUdistribution(10, 0.2); // numero de 0 a restParticles

	// origen de la nueva particula
	Vector3 origen2;
	// velocidad para la nueva particula
	Vector3 velocity;
	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
	// tiempo de vida para la nueva particula
	float lifetime;
	// cantidad de particulas que se van a generar
	int particlesGenerated = numPartsUniform(generator);

	for (int i = 0; i < particlesGenerated; i++) {
		// aleatorizamos las variabes asignadas a las nuevas particulas
		origen2 = origen;
		origen2.x = posXZUniform(generator);
		origen2.y = posYUniform(generator);
		origen2.z = posXZUniform(generator);

		lifetime = lifeTimeUdistribution(generator);

		// creamos la nueva particula
		Particle* aux = new Particle("Object" + to_string(nGameObjectsTotal), scene, origen2);
		aux->setVelocity(velocity);
		//aux->setSize(0.25);
		aux->setStartLifeTime(lifetime);
		aux->applyGravity();
		aux->setMass(massUdistribution(generator));

		// añadimos las particulas a la lista
		generatedGameObjects[aux] = true; // Aniaadir al mapa
		scene->addGameObject(aux, this); // Aniadir a la escena y pasar referencia del generador
		nGameObjects++;
		nGameObjectsTotal++;

	}



}
