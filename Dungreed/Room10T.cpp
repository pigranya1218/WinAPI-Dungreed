#include "Room10T.h"
#include "StageManager.h"

void Room10T::init()
{
   Stage::init();
   _tileImage = IMAGE_MANAGER->findImage("sampleTile1");
   loadMap("room/Stage10_T.map");
  

   //_respawnPosition[1] = Vector2(700, 250);
   
}

void Room10T::release()
{
	Stage::release();
}

void Room10T::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room10T::render()
{
	Stage::render();
}
