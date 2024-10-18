#pragma once
#include <vector>

#include "Object.h"

using namespace std;

class Scene
{
protected:
	vector<Object*> objects;

public:
	Scene();
	~Scene();

	void update(double t);
	void addObject(Object* obj);
};

