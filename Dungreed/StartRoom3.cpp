#include "StartRoom3.h"

void StartRoom3::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom3_B.map");

	// makeDoor(Vector2(TILESIZE * 24 + TILESIZE * 0.5, TILESIZE * 9), DIRECTION::DOWN);	
	_respawnPosition[0] = Vector2(300, 650); // �� ó�� �ʱ�ȭ�Ǵ� ��ġ
	_respawnPosition[3] = Vector2(600, 650); // �����ʿ��� ���� �� ��ġ

	_objectMgr->spawnObject(0x0000, Vector2(400, 300));

	_objectMgr->spawnObject(0x0001, Vector2(200, 600));
	_objectMgr->spawnObject(0x0001, Vector2(280, 600));
	

	_objectMgr->spawnObject(0x0002, Vector2(600, 300));
}

void StartRoom3::release()
{
	Stage::release();
}

void StartRoom3::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void StartRoom3::render()
{
	Stage::render();
}
