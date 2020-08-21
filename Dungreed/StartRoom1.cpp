#include "StartRoom1.h"
#include "StageManager.h"

void StartRoom1::init()
{
	
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom1_r.map");
	//_direction.push_back(DIRECTION::RIGHT);
	
	//makeDoor(Vector2(TILESIZE * 19 + TILESIZE * 0.5, TILESIZE * 10), DIRECTION::RIGHT);
	_respawnPosition[0] = Vector2(500,600); // 맨 처음 초기화되는 위치
	_respawnPosition[2] = Vector2(); // 오른쪽에서 들어올 때 위치
}

void StartRoom1::release()
{
	Stage::release();
}

void StartRoom1::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	int stageWidth = _tile[0].tileX*TILESIZE;
	if (_stageManager->getPlayerPos().x >= stageWidth)
	{
		_stageManager->setPlayerPos(200, 900);
		
		//_stageManager->moveRoom();
		
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		//_stageManager->moveRoom();
		
	}

}

void StartRoom1::render()
{
	Stage::render();

}
