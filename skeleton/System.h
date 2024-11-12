#pragma once
#include <vector>
#include "Generator.h"
#include "Scene.h"

using namespace std;

class System : public Object
{
private:
	vector<Generator*> generators;
	Scene* scene;

public:
	System(Scene* scn);
	~System();

	bool update(double t) override;

	void addGenerator(Generator* generator);
};

