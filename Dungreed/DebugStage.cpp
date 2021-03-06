#include "DebugStage.h"
#include "StageManager.h"

void DebugStage::init()
{
	int stageWidth = _tile[0].tileX*TILESIZE;
	int stageHeight = _tile[0].tileY*TILESIZE;
	_stageManager->setPlayerPos(800, 1000);


	Stage::init();
	// 맵 불러오기
	_respawnPosition[0] = Vector2(800, 1000);
	

	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage20_LB.map");

	





	

	//몹 소환
	
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	// 에너미 테스트입니다.
	
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::MINOTAURS, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_RED, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(WINSIZEX / 2 + 400, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));	
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_DOG, Vector2(WINSIZEX / 2 + 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::GHOST, Vector2(WINSIZEX / 2 + 600, WINSIZEY / 2 + 200));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::GHOST, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2, WINSIZEY / 2 + 700));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2 - 50, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2 - 150, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2 - 200, WINSIZEY / 2 + 800), true);
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_RED, Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2 + 800), true);

	
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::OVIBOS, Vector2(WINSIZEX / 2, WINSIZEY / 2), true);
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));

	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BELIAL, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2 + 100));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::NIFLHEIM, Vector2(WINSIZEX / 2 + 800, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(WINSIZEX / 2 + 500, WINSIZEY / 2 + 700), true);
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2 + 600), true);
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(WINSIZEX / 2 + 400, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_RED, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::MINOTAURS, Vector2(WINSIZEX / 2 + 300, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::GHOST, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::OVIBOS, Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2 + 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(WINSIZEX / 2 + 600, WINSIZEY / 2 + 200));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_DOG, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BELIAL, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2 + 100));

	//_enemyMgr->spawnEnemy(ENEMY_TYPE::NIFLHEIM, Vector2(WINSIZEX / 2 + 800, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(WINSIZEX / 2 + 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(WINSIZEX / 2 + 300, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_BOMB, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2 + 100));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(WINSIZEX / 2 + 400, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_RED, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::MINOTAURS, Vector2(WINSIZEX / 2 + 300, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2 + 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_BOMB, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2 + 100));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::GHOST, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::OVIBOS, Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(WINSIZEX / 2 + 600, WINSIZEY / 2 + 200));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BELIAL, Vector2(WINSIZEX / 2 + 30, WINSIZEY / 2 + 300));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_DOG, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));

	//_npcMgr->spawnNpc(NPC_TYPE::RESTAURANT, Vector2(220, 210), DIRECTION::RIGHT);

	/*_objectMgr->spawnObject(0x0000, Vector2(600, 200));
	_objectMgr->spawnObject(0x0001, Vector2(750, 200));
	_objectMgr->spawnObject(0x0002, Vector2(900, 200));

	_objectMgr->spawnObject(0x0001, Vector2(700, 500));
	_objectMgr->spawnObject(0x0001, Vector2(740, 500));
	_objectMgr->spawnObject(0x0002, Vector2(780, 500));

	_objectMgr->spawnObject(0x0000, Vector2(700, 900));
	_objectMgr->spawnObject(0x0000, Vector2(740, 900));
	_objectMgr->spawnObject(0x0001, Vector2(780, 900));*/


	//_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(900, 500), DIRECTION::LEFT);
	
	//makeDoor(Vector2(400, 300), DIRECTION::LEFT);
	_torchImg = IMAGE_MANAGER->findImage("Torch");
	_torchAni = new Animation;
	_torchAni->init(_torchImg->getWidth(), _torchImg->getHeight(), _torchImg->getMaxFrameX(), _torchImg->getMaxFrameY());
	_torchAni->setDefPlayFrame(false, true);
	_torchAni->setFPS(15);
	_torchAni->start();
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

	// CAMERA->setXY(_stageManager->getPlayerPos());

	if (KEY_MANAGER->isOnceKeyDown('L'))
	{
		for (int i = 0; i < 4; i++)
		{
			if (_doors[i] != nullptr)
			{
				_doors[i]->setOpen(true);
			}
		}
	}
	_torchAni->frameUpdate(elapsedTime);
}

void DebugStage::render()
{
	Stage::render();

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;

	/*IMAGE_MANAGER->findImage("Tavern")->setScale(4);
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 648));*/

	Image* table = IMAGE_MANAGER->findImage("TortureTable1");
	table->setScale(4);
	table->render(CAMERA->getRelativeV2(Vector2(1200, 1110)));

	Image* cell = IMAGE_MANAGER->findImage("BrokenCell");
	cell->setScale(4);
	cell->render(CAMERA->getRelativeV2(Vector2(300, 2094)));

	Image* table2 = IMAGE_MANAGER->findImage("TortureTable1");
	table->setScale(4);
	table->render(CAMERA->getRelativeV2(Vector2(1000, 794)));
}
