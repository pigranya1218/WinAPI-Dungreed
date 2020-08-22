#include "VillageStage.h"
#include "StageManager.h"



void VillageStage::init()
{
	

	Stage::init();

	_respawnPosition[0] = Vector2(4600, 1000);

	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(0, 950), Vector2(2005, 950), Vector2(0,2005),Vector2(500,2000)));
	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(2005, 950), Vector2(2640, 1590),Vector2(2005,2640),Vector2(950,1590)));
	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(2640, 1590), Vector2(2718, 1590),Vector2(2640,2718),Vector2(1300,1700)));
	
	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(3110, 1585), Vector2(3265, 1585),Vector2(3110,3265),Vector2(1300,1700)));
	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(3265, 1585), Vector2(3750, 1105),Vector2(3265,3750),Vector2(1585,1105)));
	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(3750, 1105), Vector2(5910, 1105), Vector2(3750,5910),Vector2(1000,1200)));
	

	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(5910, 1105), Vector2(6388, 1585), Vector2(5910,6388),Vector2(1105,1585)));
	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(6388, 1585), Vector2(6546, 1585), Vector2(6388,6546),Vector2(1400,1600)));


	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(7033, 1590), Vector2(7115, 1590), Vector2(7033,7115),Vector2(1400,1700)));
	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(7115, 1590), Vector2(7750, 950), Vector2(7115,7750),Vector2(1590,950)));
	_collisionPlatforms.push_back( LinearFunc::getLinearFuncFromPoints(Vector2(7750, 950), Vector2(9800, 950), Vector2(7750,9800),Vector2(800,1100)));


	_BGL = IMAGE_MANAGER->findImage("Town_BGL");
	_BG1 = IMAGE_MANAGER->findImage("Town_BG");
	_BG2 = IMAGE_MANAGER->findImage("Town_BG2");
	_floor = IMAGE_MANAGER->findImage("Town_Floor");
	
	_dungeonEat = IMAGE_MANAGER->findImage("DungeonEat");
	_eatAni = new Animation;
	_eatAni->init(_dungeonEat->getWidth(), _dungeonEat->getHeight(), _dungeonEat->getMaxFrameX(), _dungeonEat->getMaxFrameY());
	_eatAni->setDefPlayFrame(false, false);
	_eatAni->setFPS(12);
	

	//CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 9000, 500);
	
	_tileImage = IMAGE_MANAGER->findImage("sampleTile3");
	loadMap("Town.map");

	_enter = false;

	SOUND_MANAGER->stop("Villiage_BGM");
	SOUND_MANAGER->play("Villiage_BGM", 1.0f);

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
	
	

	if (_stageManager->getPlayerPos().x >= 4000 && _stageManager->getPlayerPos().x <= 5800 && _stageManager->getPlayerPos().y >= 1600)
	{
		if(!_enter)
		enterDungeon();
	}
		//_stageManager->nextStage();
	if (_enter)
	{
		if (_eatAni->getPlayIndex() >= 9)
		{
			_stageManager->setShowPlayer(false);
		}

		if (!_eatAni->isPlay())
		{
			_stageManager->nextStage();

		}
	}
	
	
	_eatAni->frameUpdate(elapsedTime);
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

	//CAMERA->aniRender()
	if (_enter)
	{
		_dungeonEat->setScale(4);
		_dungeonEat->aniRender(CAMERA->getRelativeV2(_eatPos), _eatAni);
	}
	Stage::render();


	IMAGE_MANAGER->findImage("TempleFront")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("TempleFront"), Vector2(4730, 1047 - IMAGE_MANAGER->findImage("TempleFront")->getHeight() * 2));
}

void VillageStage::enterDungeon()
{
	SOUND_MANAGER->stop("Villiage_BGM");

	SOUND_MANAGER->stop("DungeonEat");
	SOUND_MANAGER->play("DungeonEat", 1.0f);

	_eatPos.x = _stageManager->getPlayerPos().x;
	_eatPos.y= _stageManager->getPlayerPos().y-_dungeonEat->getHeight()-35;
	_enter = true;
	_eatAni->start();


}





