#include "StageManager.h"
#include "Stage.h"
#include "Player.h"

void Stage::init()
{
	_objectMgr = new ObjectManager;
	
	_npcMgr = new NpcManager;
	
	_enemyMgr = new EnemyManager;
	
	_projectileMgr = new ProjectileManager;
	_projectileMgr->setStage(this);
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
	_projectileMgr->update(elaspedTime);
	_objectMgr->update(elaspedTime);
	_npcMgr->update(elaspedTime);
	_enemyMgr->update(elaspedTime);
	
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
	Vector2 lastCenter = object->getPosition();
	Vector2 newCenter = lastCenter + moveDir;
	float radiusX = object->getSize().x / 2;
	float radiusY = object->getSize().y / 2;
	int calculatePoint[4][2] = { {-1, -1}, {1, -1}, {1, 1}, {-1, 1}}; // �»�, ���, ����, ����
	Vector2 lastPoints[4];
	Vector2 newPoints[4];
	for (int i = 0; i < 4; i++)
	{
		lastPoints[i] = Vector2(lastCenter.x + calculatePoint[i][0] * radiusX, lastCenter.y + calculatePoint[i][1] * radiusY);
		newPoints[i] = Vector2(newCenter.x + calculatePoint[i][0] * radiusX, newCenter.y + calculatePoint[i][1] * radiusY);
	}

	// ���� �˻�
	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		for (int j = 2; j <= 3; j++) // �Ʒ� �������鸸 �˻�
		{
			bool isCollision = false;
			if (_collisionPlatforms[i].func.a == LinearFunc::INF_A) // ������
			{
				// ������ �������� ���� ����
			}
			else // �������� �ƴ� ���
			{
				if (_collisionPlatforms[i].func.start <= newPoints[j].x && newPoints[j].x <= _collisionPlatforms[i].func.end) // ���� �ȿ� ���� ��
				{
					// ���������� ���� ���� �ִٰ�, �̹� ������Ʈ���� ���� �Ʒ��� �������ٸ� ���ǿ� �ö�Ÿ�� �Ѵ�

					LINEAR_VALUE_TYPE leftFoot = _collisionPlatforms[i].func.getValueType(lastPoints[3].x, lastPoints[3].y);
					LINEAR_VALUE_TYPE rightFoot = _collisionPlatforms[i].func.getValueType(lastPoints[2].x, lastPoints[2].y);
					if ((leftFoot != _collisionPlatforms[i].collision) &&
						(rightFoot != _collisionPlatforms[i].collision) &&
						(_collisionPlatforms[i].func.getValueType(newPoints[j].x, newPoints[j].y) == _collisionPlatforms[i].collision))
					{
						newPoints[j].y = _collisionPlatforms[i].func.getY(newPoints[j].x);
						isCollision = true;
						if (_collisionPlatforms[i].collision == LINEAR_VALUE_TYPE::DOWN)
						{
							object->setIsStand(true); // ���� ���ִ� ���
						}
					}
				}
			}
			if (isCollision)
			{
				newCenter = Vector2(newPoints[j].x - calculatePoint[j][0] * radiusX, newPoints[j].y - calculatePoint[j][1] * radiusY);
				for (int k = 0; k < 4; k++)
				{
					newPoints[k] = Vector2(newCenter.x + calculatePoint[k][0] * radiusX, newCenter.y + calculatePoint[k][1] * radiusY);
				}
			}
		}
	}

	// �� �˻�
	for (int i = 0; i < _collisionGrounds.size(); i++)
	{
		for (int j = 0; j < 4; j++) // �� �������� �˻�
		{
			bool isCollision = false;
			if (_collisionGrounds[i].func.a == LinearFunc::INF_A) // ������
			{
				if (_collisionGrounds[i].func.start <= newPoints[j].y && newPoints[j].y <= _collisionGrounds[i].func.end) // ���� �ȿ� ���� ��
				{
					if (_collisionGrounds[i].func.getValueType(newPoints[j].x, newPoints[j].y) == _collisionGrounds[i].collision)
					{
						newPoints[j].x = _collisionGrounds[i].func.b;
						isCollision = true;
					}
				}
			}
			else // �������� �ƴ� ���
			{
				if (_collisionGrounds[i].func.start <= newPoints[j].x && newPoints[j].x <= _collisionGrounds[i].func.end) // ���� �ȿ� ���� ��
				{
					if (_collisionGrounds[i].func.getValueType(newPoints[j].x, newPoints[j].y) == _collisionGrounds[i].collision)
					{
						newPoints[j].y = _collisionGrounds[i].func.getY(newPoints[j].x);
						isCollision = true;
						if (_collisionGrounds[i].collision == LINEAR_VALUE_TYPE::DOWN)
						{
							object->setIsStand(true); // ���� ���ִ� ���
						}
					}
				}
			}
			if (isCollision)
			{
				newCenter = Vector2(newPoints[j].x - calculatePoint[j][0] * radiusX, newPoints[j].y - calculatePoint[j][1] * radiusY);
				for (int k = 0; k < 4; k++)
				{
					newPoints[k] = Vector2(newCenter.x + calculatePoint[k][0] * radiusX, newCenter.y + calculatePoint[k][1] * radiusY);
				}
			}
		}
	}

	object->setPosition(newCenter);
}

void Stage::attack(FloatRect* rect, AttackInfo* info)
{
}

void Stage::attack(FloatCircle* circle, AttackInfo* info)
{
}

void Stage::attack(Projectile* projectile, AttackInfo* info)
{
	_projectileMgr->addProjectile(projectile);
}

Vector2 Stage::getPlayerPos()
{
	return _stageManager->getPlayerPos();
}
