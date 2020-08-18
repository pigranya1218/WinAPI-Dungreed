#include "StartRoom1.h"
#include "StageManager.h"

void StartRoom1::init()
{
	
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("StartRoom1.map");
	//_direction.push_back(DIRECTION::RIGHT);
	
	_OpenDirection[0] = false;
	_OpenDirection[1] = false;
	_OpenDirection[2] = true;
	_OpenDirection[3] = false;
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
		
		_stageManager->moveRoom();
		_stageManager->makeStage();
	}

}

void StartRoom1::render()
{
	Stage::render();

}
