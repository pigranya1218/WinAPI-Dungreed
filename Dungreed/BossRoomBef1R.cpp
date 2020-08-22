#include "BossRoomBef1R.h"

void BossRoomBef1R::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/BossRoomBef1.map");

	_respawnPosition[0] = Vector2(570, 670);
}

void BossRoomBef1R::release()
{
	Stage::release();
}

void BossRoomBef1R::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void BossRoomBef1R::render()
{
	Stage::render();
}
