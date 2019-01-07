#pragma once
#include <vector>

#include "GameObject.h"

struct GameObjectVector
{
public:
	std::vector<GameObject*> objects;
	void clear(btDiscreteDynamicsWorld *dynamicWorld)
	{
		auto iter = objects.begin();

		while (iter != objects.end())
		{
			if ((*iter))
			{
				btRigidBody * rb = (*iter)->GetRigidBody();
				dynamicWorld->removeRigidBody(rb);

				//delete (*iter);
				iter = objects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
};

class GameObjectCollection
{
private:
	std::vector<GameObjectVector*> objectsByLayer; // point to vector of objects in that layer
	btDiscreteDynamicsWorld *dynamicWorld;

public:
	GameObjectCollection(btDiscreteDynamicsWorld *dynamicWorld);
	~GameObjectCollection();
	void append(GameObject *object);
	std::vector<GameObject*> getObjectsByLayer(RenderLayers layer);
	void clear();
	void updateAll(float deltaTime);
	void updateLayer(RenderLayers layer, float deltaTime);
};
