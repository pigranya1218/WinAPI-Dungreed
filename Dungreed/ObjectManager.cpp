#include "stdafx.h"
#include "ObjectManager.h"

void ObjectManager::init()
{
}

void ObjectManager::release()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->release();
	}
}

void ObjectManager::update(float const elapsedTime)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->update(elapsedTime);
	}
}

void ObjectManager::render()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->render();
	}
}
