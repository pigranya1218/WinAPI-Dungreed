#pragma once
#include "GameObject.h"

class EnemyManager;

class Enemy : public GameObject
{
protected:
	EnemyManager* _enemyManager;

public:
	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
};

