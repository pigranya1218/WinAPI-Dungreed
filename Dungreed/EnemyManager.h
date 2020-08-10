#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Banshee.h"
#include "BatRed.h"
#include "SkelBigIce.h"
#include "GameObject.h"

class EnemyManager
{
private:
	vector<Enemy*> _vEnemy;		// 에너미 담을 벡터

	class TestScene* _scene;

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void spawn(const Vector2& pos, ENEMY_TYPE enemyType, DIRECTION direction = DIRECTION::LEFT);

	void setScene(class TestScene* scene) { _scene = scene; }

	void moveEnemy(GameObject* gObject, Vector2& pos);
};

