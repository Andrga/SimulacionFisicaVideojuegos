#pragma once
#include "../../basics/RBStatic.h"

class Scene;
class ForceSystem;

class Planeta
{
private:
	Scene* scene = nullptr;
	vector<RBStatic*>planeta;

	float rotAngle = 0.1;
public:
	Planeta(Scene* scn, PxPhysics* gPhysics, PxScene* gScene, int id, ForceSystem* fsys, float angle);
	~Planeta();

	void update(double t);

	Vector3 rotateZ(const Vector3& v);
};

