#include "DebugStage.h"
#include "StageManager.h"

void DebugStage::init()
{
	Stage::init();

	

	// �� �ҷ�����
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("testStage.map");

	// ���ʹ� �׽�Ʈ�Դϴ�.
	_enemyMgr->setStage(this);
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));

	_npcMgr->setStage(this);
	_npcMgr->spawnNpc(NPC_TYPE::RESTAURANT, Vector2(220, 210), DIRECTION::RIGHT);
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
