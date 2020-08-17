#include "VillageStage.h"
#include "StageManager.h"

void VillageStage::init()
{
	Stage::init();

	/*_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 950), Vector2(2005, 950)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(2005, 950), Vector2(2640, 1590)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(2640, 1590), Vector2(2718, 1590)), LINEAR_VALUE_TYPE::DOWN });
	
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(3110, 1585), Vector2(3265, 1585)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(3265, 1585), Vector2(3750, 1105)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(3750, 1105), Vector2(5910, 1105)), LINEAR_VALUE_TYPE::DOWN });
	

	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(5910, 1105), Vector2(6388, 1585)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(6388, 1585), Vector2(6546, 1585)), LINEAR_VALUE_TYPE::DOWN });


	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(7033, 1590), Vector2(7115, 1590)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(7115, 1590), Vector2(7750, 950)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(7750, 950), Vector2(9800, 950)), LINEAR_VALUE_TYPE::DOWN });*/


	_BGL = IMAGE_MANAGER->findImage("Town_BGL");
	_BG1 = IMAGE_MANAGER->findImage("Town_BG");
	_BG2 = IMAGE_MANAGER->findImage("Town_BG2");
	_floor = IMAGE_MANAGER->findImage("Town_Floor");



	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 9000, 500);
	
	_tileImage = IMAGE_MANAGER->findImage("sampleTile3");
	loadMap("Town3.map");

	//_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2()) }
}

void VillageStage::release()
{
	Stage::release();
}

void VillageStage::update(float const elapsedTime)
{
	/*int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, stageWidth - WINSIZEX, stageHeight - WINSIZEY);*/

	Stage::update(elapsedTime);
	
	//CAMERA->setXY(_stageManager->getPlayerPos());
}

void VillageStage::render()
{
	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;


	//_BGL->setScale(5);
	_BGL->render(Vector2(WINSIZEX/2,WINSIZEY/2),Vector2(WINSIZEX, WINSIZEY));

	for (int i = 0; i < stageWidth / _BG1->getWidth(); i++)
	{
		_BG1->setScale(6);
		CAMERA->render(_BG1, Vector2(WINSIZEX/2+i* _BG1->getWidth()*6, stageHeight - 900));
		_BG2->setScale(5);
		CAMERA->render(_BG2, Vector2(WINSIZEX / 2 + i * _BG2->getWidth() * 5, stageHeight - 480));
	}
	_floor->setScale(5);
	CAMERA->render(_floor,Vector2(5000, WINSIZEY / 2 + 470));

	//의상실
	IMAGE_MANAGER->findImage("Boutique")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Boutique"), Vector2(1000, 560));
	//템플
	IMAGE_MANAGER->findImage("Temple")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Temple"), Vector2(4830, 1047- IMAGE_MANAGER->findImage("Temple")->getHeight()*2));

	IMAGE_MANAGER->findImage("Shop")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Shop"), Vector2(8300, 617));

	IMAGE_MANAGER->findImage("Gunsmith")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Gunsmith"), Vector2(9200, 617));

	IMAGE_MANAGER->findImage("BlackSmith")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("BlackSmith"), Vector2(8750, 1340));

	IMAGE_MANAGER->findImage("BlackSmithDisplay")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("BlackSmithDisplay"), Vector2(8750, 1600));

	IMAGE_MANAGER->findImage("TrainingSchool")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("TrainingSchool"), Vector2(950, 1490));

	IMAGE_MANAGER->findImage("TrainingHouse")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("TrainingHouse"), Vector2(650, 1400));

	IMAGE_MANAGER->findImage("Well")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Well"), Vector2(7450, 1550));

	IMAGE_MANAGER->findImage("Tree0")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Tree0"), Vector2(2150, 1520));


	Stage::render();

	IMAGE_MANAGER->findImage("TempleFront")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("TempleFront"), Vector2(4730, 1047 - IMAGE_MANAGER->findImage("TempleFront")->getHeight() * 2));
}





