#include "StartRoom1.h"
#include "StageManager.h"

void StartRoom1::init()
{
	
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom1_R.map");
	//_direction.push_back(DIRECTION::RIGHT);
	
	//makeDoor(Vector2(TILESIZE * 19 + TILESIZE * 0.5, TILESIZE * 10), DIRECTION::RIGHT);
	_respawnPosition[0] = Vector2(570,670); // 맨 처음 초기화되는 위치
	_respawnPosition[2] = Vector2(1130,670); // 오른쪽에서 들어올 때 위치

	_objectMgr->spawnObject(0x0000, Vector2(500, 600));
	_objectMgr->spawnObject(0x0001, Vector2(200, 600));
	_objectMgr->spawnObject(0x0001, Vector2(380, 600));
	_objectMgr->spawnObject(0x0001, Vector2(430, 600));
	_objectMgr->spawnObject(0x0002, Vector2(300, 600));
}

void StartRoom1::release()
{
	Stage::release();
}

void StartRoom1::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	int stageWidth = _tile[0].tileX*TILESIZE;
	/*if (_stageManager->getPlayerPos().x >= stageWidth)
	{
		_stageManager->setPlayerPos(200, 900);
		
		
		
	}*/
	

}

void StartRoom1::render()
{
	Stage::render();

}
