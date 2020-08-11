#include "TestStage.h"

void TestStage::init()
{
	Stage::init();
	_collisions.push_back({LinearFunc::getLinearFuncFromPoints(Vector2(0, 800), Vector2(WINSIZEX, 800)), LINEAR_VALUE_TYPE::DOWN});
	_collisions.push_back({LinearFunc::getLinearFuncFromPoints(Vector2(300, 800), Vector2(1550, -450)), LINEAR_VALUE_TYPE::DOWN});
	_collisions.push_back({LinearFunc::getLinearFuncFromPoints(Vector2(50, 100), Vector2(50, 800)), LINEAR_VALUE_TYPE::LEFT});
	_collisions.push_back({LinearFunc::getLinearFuncFromPoints(Vector2(1550, 100), Vector2(1550, 800)), LINEAR_VALUE_TYPE::RIGHT});
	_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 100), Vector2(WINSIZEX, 100)), LINEAR_VALUE_TYPE::UP });

	
	// 에너미 테스트입니다.
	_enemyMgr->setStage(this);
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_RED, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_collisions.push_back({LinearFunc::getLinearFuncFromPoints(Vector2(300, 800), Vector2(1550, -450)), LINEAR_VALUE_TYPE::DOWN});
}

void TestStage::release()
{
	Stage::release();
}

void TestStage::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void TestStage::render()
{
	for (int i = 0; i < _collisions.size(); i++)
	{
		D2D_RENDERER->drawLine(_collisions[i].func.getStart(), _collisions[i].func.getEnd());
	}

	Stage::render();

}
