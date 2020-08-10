#include "Stage.h"

void Stage::init()
{
	_objectMgr = new ObjectManager;
	_npcMgr = new NpcManager;
	_enemyMgr = new EnemyManager;
	_projectileMgr = new ProjectileManager;
}

void Stage::release()
{
	_objectMgr->release();
	delete _objectMgr;
	_npcMgr->release();
	delete _npcMgr; 
	_enemyMgr->release();
	delete _enemyMgr; 
	_projectileMgr->release();
	delete _projectileMgr;
}

void Stage::update(float const elaspedTime)
{
	_objectMgr->update(elaspedTime);
	_npcMgr->update(elaspedTime);
	_enemyMgr->update(elaspedTime);
	_projectileMgr->update(elaspedTime);
}

void Stage::render()
{
	_objectMgr->render();
	_npcMgr->render();
	_enemyMgr->render();
	_projectileMgr->render();
}

void Stage::moveTo(GameObject* object, Vector2 const moveDir)
{
	object->setIsStand(false);
	Vector2 newCenter = object->getPosition() + moveDir;
	float radiusX = object->getSize().x / 2;
	float radiusY = object->getSize().y / 2;
	int calculatePoint[4][2] = { {-1, -1}, {1, -1}, {1, 1}, {-1, 1}}; // 좌상, 우상, 우하, 좌하
	Vector2 points[4];
	for (int i = 0; i < 4; i++)
	{
		points[i] = Vector2(newCenter.x + calculatePoint[i][0] * radiusX, newCenter.y + calculatePoint[i][1] * radiusY);
	}

	for (int i = 0; i < _collisions.size(); i++)
	{
		for (int j = 0; j < 4; j++) // 각 꼭짓점별 검사
		{
			bool isCollision = false;
			if (_collisions[i].func.a == LinearFunc::INF_A) // 수직선
			{
				if (_collisions[i].func.start <= points[j].y && points[j].y <= _collisions[i].func.end) // 범위 안에 있을 때
				{
					if (_collisions[i].func.getValueType(points[j].x, points[j].y) == _collisions[i].collision)
					{
						points[j].x = _collisions[i].func.b;
						isCollision = true;
					}
				}
			}
			else // 수직선이 아닌 경우
			{
				if (_collisions[i].func.start <= points[j].x && points[j].x <= _collisions[i].func.end) // 범위 안에 있을 때
				{
					if (_collisions[i].func.getValueType(points[j].x, points[j].y) == _collisions[i].collision)
					{
						points[j].y = _collisions[i].func.getY(points[j].x);
						isCollision = true;
						object->setIsStand(true); // 땅에 서있는 경우
					}
				}
			}
			if (isCollision)
			{
				newCenter = Vector2(points[j].x - calculatePoint[j][0] * radiusX, points[j].y - calculatePoint[j][1] * radiusY);
				for (int k = 0; k < 4; k++)
				{
					points[k] = Vector2(newCenter.x + calculatePoint[k][0] * radiusX, newCenter.y + calculatePoint[k][1] * radiusY);
				}
			}
		}
	}

	object->setPosition(newCenter);
}
