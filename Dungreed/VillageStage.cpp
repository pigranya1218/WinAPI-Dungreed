#include "VillageStage.h"

void VillageStage::init()
{
	Stage::init();

	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 800), Vector2(WINSIZEX, 800)), LINEAR_VALUE_TYPE::DOWN });

	_BGL = IMAGE_MANAGER->findImage("Town_BGL");
	_BG1 = IMAGE_MANAGER->findImage("Town_BG");
	_BG2 = IMAGE_MANAGER->findImage("Town_BG2");
	_floor = IMAGE_MANAGER->findImage("Town_Floor");

	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, _BGL->getWidth()*6-WINSIZEX, 1600);

	//_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2()) }
}

void VillageStage::release()
{
	Stage::release();
}

void VillageStage::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	
}

void VillageStage::render()
{
	_BGL->setScale(6);
	CAMERA->render(_BGL, Vector2(WINSIZEX / 2, WINSIZEY / 2),Vector2((int)_BGL->getWidth(), _BGL->getHeight()));
	_BG1->setScale(6);
	CAMERA->render(_BG1, Vector2(WINSIZEX / 2, WINSIZEY / 2 + 200));
	_BG2->setScale(6);
	CAMERA->render(_BG2, Vector2(WINSIZEX / 2, WINSIZEY / 2 + 200));
	

	Stage::render();
}
