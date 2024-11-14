#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(Scene* scn)
{
	if (scn != nullptr) {
		scenes.push_back(scn);
		scn->setup();
	}
}

void SceneManager::update(float t)
{
	scenes[actualScene]->update(t);
}

void SceneManager::setScene(int id)
{
	scenes[actualScene]->hide();
	actualScene = id;
	scenes[actualScene]->show();
}
