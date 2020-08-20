#include "stdafx.h"
#include "ObjectManager.h"
#include "Stage.h"
#include "BrokenObject.h"

void ObjectManager::init()
{
}

void ObjectManager::release()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->release();
		delete _objects[i];
	}
}

void ObjectManager::update(float const elapsedTime)
{
	for (int i = 0; i < _objects.size();)
	{
		_objects[i]->update(elapsedTime);
		if (!_objects[i]->getActive())
		{
			_objects[i]->release();
			delete _objects[i];
			_objects.erase(_objects.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void ObjectManager::render()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->render();
	}
}

bool ObjectManager::isHit(FloatRect* rect, AttackInfo* info)
{
	bool result = false;
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i]->isHit(rect, info))
		{
			result = _objects[i]->hitEffect(rect, info);
		}
	}
	return false;
}

bool ObjectManager::isHit(FloatCircle* circle, AttackInfo* info)
{
	bool result = false;
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i]->isHit(circle, info))
		{
			result = _objects[i]->hitEffect(circle, info);
		}
	}
	return false;
}

bool ObjectManager::isHit(Projectile* projectile, bool isOnceCollision)
{
	bool result = false;
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i]->isHit(projectile))
		{
			result = _objects[i]->hitEffect(projectile);
			if (result)
			{
				return result;
			}
		}
	}
	return false;
}

void ObjectManager::moveTo(GameObject* gameObject, Vector2 moveDir, bool checkCollisionGround, bool checkCollisionPlatform)
{
	_stage->moveTo(gameObject, moveDir, checkCollisionGround, checkCollisionPlatform);
}

void ObjectManager::spawnObject(int objectCode, Vector2 pos)
{
	switch (objectCode)
	{
	case 0x0000: // 드럼
	case 0x0001: // 박스
	case 0x0002: // 큰 박스
	{
		BrokenObject* newObject = new BrokenObject;
		newObject->init(objectCode, pos);
		newObject->setObjectManager(this);
		_objects.push_back(newObject);
	}
	break;
	}
}

void ObjectManager::pushObject(Object* object)
{
	_objects.push_back(object);
}
