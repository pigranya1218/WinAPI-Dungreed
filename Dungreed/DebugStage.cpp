
#include "DebugStage.h"

void DebugStage::init()
{
	Stage::init();
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 800), Vector2(WINSIZEX, 800)), LINEAR_VALUE_TYPE::DOWN });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 100), Vector2(WINSIZEX, 100)), LINEAR_VALUE_TYPE::UP });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(50, 100), Vector2(50, 800)), LINEAR_VALUE_TYPE::LEFT });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1550, 100), Vector2(1550, 800)), LINEAR_VALUE_TYPE::RIGHT });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1250, 800), Vector2(1400, 650)), LINEAR_VALUE_TYPE::DOWN });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1400, 650), Vector2(1550, 650)), LINEAR_VALUE_TYPE::DOWN });
	
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(200, 700), Vector2(300, 700)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(300, 700), Vector2(700, 300)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(700, 300), Vector2(1550, 300)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1100, 500), Vector2(1250, 500)), LINEAR_VALUE_TYPE::DOWN });


	// ���ʹ� �׽�Ʈ�Դϴ�.
	_enemyMgr->setStage(this);
	/*_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_RED, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2));*/
}

void DebugStage::release()
{
	Stage::release();

}

void DebugStage::update(float const elapsedTime)
{
	Stage::update(elapsedTime);

}

void DebugStage::render()
{
	for (int i = 0; i < _collisionGrounds.size(); i++)
	{
		D2D_RENDERER->drawLine(_collisionGrounds[i].func.getStart(), _collisionGrounds[i].func.getEnd(), D2D1::ColorF::Enum::Red, 1);
	}

	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		D2D_RENDERER->drawLine(_collisionPlatforms[i].func.getStart(), _collisionPlatforms[i].func.getEnd(), D2D1::ColorF::Enum::Blue, 1);
	}

	Stage::render();
}

void DebugStage::mapLoad()
{
	HANDLE stageFile;
	DWORD read;

	stageFile = CreateFile("stage5.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(stageFile, _tile, sizeof(tagTileMap) * TILEX * TILEY, &read, NULL);

	CloseHandle(stageFile);
}