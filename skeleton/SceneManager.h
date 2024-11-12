#pragma once
#include "Scene.h"
#include <vector>
using namespace std;

class SceneManager
{
private:
	vector<Scene*> scenes;

	int actualScene = 0;
public:
	SceneManager();
	~SceneManager();
	
	void addScene(Scene* scn);
	void update(float t);

	void setScene(int id);

};

