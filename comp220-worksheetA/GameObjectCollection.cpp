#include "GameObject.h"
#include "GameObjectCollection.h"

void GameObjectCollection::append(GameObject *object)
{
	int layer = (int)object->GetLayer();
	objectsByLayer[layer]->objects.push_back(object);
}

GameObjectCollection::GameObjectCollection(btDiscreteDynamicsWorld *dynamicWorld)
{
	// Allow us to remove rigid bodies
	this->dynamicWorld = dynamicWorld;

	// Resize so we have an index for each render layer
	objectsByLayer.resize(RenderLayers_ITEMCOUNT);

	// Add a pointer to a object containing a vector
	// To keep each render layer separate
	for (int i = 0; i < RenderLayers_ITEMCOUNT; i++)
	{
		GameObjectVector *objects = new GameObjectVector();
		objectsByLayer[i] = objects;
	};
}

// Return all objects within a specified render layer
std::vector<GameObject*> GameObjectCollection::getObjectsByLayer(RenderLayers layer)
{
	return objectsByLayer[(int)layer]->objects;
}

GameObjectCollection::~GameObjectCollection()
{
	clear();
}

void GameObjectCollection::clear()
{
	for (int i = 0; i < RenderLayers_ITEMCOUNT; i++)
	{
		// Remove rigid bodies and objects
		objectsByLayer[i]->clear(dynamicWorld);
		// Clear object vector reference
		delete objectsByLayer[i];
	};
}

void GameObjectCollection::updateAll(float deltaTime)
{
	for (int i = 0; i < RenderLayers_ITEMCOUNT; i++)
	{
		updateLayer(RenderLayers(i), deltaTime);
	};
}

void GameObjectCollection::updateLayer(RenderLayers layer, float deltaTime)
{
	for (GameObject *object : getObjectsByLayer(layer))
	{
		object->Update(deltaTime);
	}
}
