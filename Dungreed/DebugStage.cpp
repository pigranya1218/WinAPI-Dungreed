#include "DebugStage.h"
#include "StageManager.h"

void DebugStage::init()
{
	Stage::init();

	// 맵 불러오기
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("testStage.map");

	// 에너미 테스트입니다.
	_enemyMgr->setStage(this);
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::NIFLHEIM, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_RED, Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_RED, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2 + 300, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BELIAL, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_BOMB, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
}

void DebugStage::release()
{
	Stage::release();

}

void DebugStage::update(float const elapsedTime)
{
	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, stageWidth - WINSIZEX, stageHeight - WINSIZEY);

	Stage::update(elapsedTime);

	CAMERA->setXY(_stageManager->getPlayerPos());
}

void DebugStage::render()
{
	Stage::render();

	


	//CAMERA->frameRender(_tileImage, Vector2(800,400));
}
