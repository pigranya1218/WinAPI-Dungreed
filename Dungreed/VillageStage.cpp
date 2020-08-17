#include "VillageStage.h"
#include "StageManager.h"

void VillageStage::init()
{
	Stage::init();

	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 950), Vector2(2005, 950)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(2005, 950), Vector2(2640, 1590)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(2640, 1590), Vector2(2718, 1590)), LINEAR_VALUE_TYPE::DOWN });
	
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(3110, 1585), Vector2(3265, 1585)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(3265, 1585), Vector2(3750, 1105)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(3750, 1105), Vector2(5910, 1105)), LINEAR_VALUE_TYPE::DOWN });
	

	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(5910, 1105), Vector2(6388, 1585)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(6388, 1585), Vector2(6546, 1585)), LINEAR_VALUE_TYPE::DOWN });


	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(7033, 1590), Vector2(7115, 1590)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(7115, 1590), Vector2(7750, 950)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(7750, 950), Vector2(9800, 950)), LINEAR_VALUE_TYPE::DOWN });


	_BGL = IMAGE_MANAGER->findImage("Town_BGL");
	_BG1 = IMAGE_MANAGER->findImage("Town_BG");
	_BG2 = IMAGE_MANAGER->findImage("Town_BG2");
	_floor = IMAGE_MANAGER->findImage("Town_Floor");



	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 9000, 500);
	
	_tileImage = IMAGE_MANAGER->findImage("sampleTile3");
	loadMap("Town.map");

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

	for (int i = 0; i < _collisionGrounds.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionGrounds[i].func.getStart()), CAMERA->getRelativeV2(_collisionGrounds[i].func.getEnd()), D2D1::ColorF::Enum::Red, 1);
	}

	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionPlatforms[i].func.getStart()), CAMERA->getRelativeV2(_collisionPlatforms[i].func.getEnd()), D2D1::ColorF::Enum::Blue, 1);
	}

	Stage::render();

	IMAGE_MANAGER->findImage("TempleFront")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("TempleFront"), Vector2(4730, 1047 - IMAGE_MANAGER->findImage("TempleFront")->getHeight() * 2));
}

//void VillageStage::mapLoad()
//{
//	
//		HANDLE stageFile;
//		DWORD read;
//
//		stageFile = CreateFile("Town.map", GENERIC_READ, NULL, NULL,
//			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//
//		ReadFile(stageFile, _tile, sizeof(tagTileMap) * MAXTILEX*MAXTILEY, &read, NULL);
//
//		CloseHandle(stageFile);
//
//		int curr = 0;
//
//		for (int i = 0; i < _tile[0].tileX* _tile[0].tileY; ++i)
//		{
//			switch (_tile[i].linePos)
//			{
//			case DRAW_LINE_POSITION::TOP:
//
//				if (curr == 0)
//				{
//					_currentIndex = i;
//					curr++;
//				}
//
//				if (_tile[i + 1].linePos == DRAW_LINE_POSITION::TOP) continue;
//				else
//				{
//					_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)),LINEAR_VALUE_TYPE::DOWN });
//					curr = 0;
//
//				}
//
//				break;
//			case DRAW_LINE_POSITION::BOTTOM:
//
//				if (curr == 0)
//				{
//					_currentIndex = i;
//					curr++;
//				}
//
//				if (_tile[i + 1].linePos == DRAW_LINE_POSITION::BOTTOM) continue;
//				else
//				{
//					_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.bottom),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::UP });
//					curr = 0;
//				}
//
//				break;
//			case DRAW_LINE_POSITION::LEFT:
//				if (curr == 0)
//				{
//					_currentIndex = i;
//					curr++;
//				}
//
//				if (_tile[i + _tile[0].tileX + 1].linePos == DRAW_LINE_POSITION::LEFT) continue;
//				else
//				{
//					_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.left,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::RIGHT });
//					curr = 0;
//
//				}
//
//				break;
//			case DRAW_LINE_POSITION::RIGHT:
//				if (curr == 0)
//				{
//					_currentIndex = i;
//					curr++;
//				}
//
//				if (_tile[i + _tile[0].tileX + 1].linePos == DRAW_LINE_POSITION::RIGHT) continue;
//				else
//				{
//					_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.right,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::LEFT });
//					curr = 0;
//
//				}
//
//				break;
//
//			case DRAW_LINE_POSITION::LEFT_TOP:
//				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.top),Vector2(_tile[i].rc.left,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::RIGHT });
//				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)),LINEAR_VALUE_TYPE::DOWN });
//				break;
//			case DRAW_LINE_POSITION::LEFT_BOTTOM:
//				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.top),Vector2(_tile[i].rc.left,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::RIGHT });
//				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.bottom),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::UP });
//				break;
//			case DRAW_LINE_POSITION::RIGHT_TOP:
//				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)),LINEAR_VALUE_TYPE::DOWN });
//				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.right,_tile[i].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::LEFT });
//				break;
//			case DRAW_LINE_POSITION::RIGHT_BOTTOM:
//				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.right,_tile[i].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::LEFT });
//				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.bottom),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::UP });
//				break;
//			case DRAW_LINE_POSITION::LEFT_DIAGONAL:
//				if (curr == 0)
//				{
//					_currentIndex = i;
//					curr++;
//				}
//
//				if (_tile[i + _tile[0].tileX - 2].linePos == DRAW_LINE_POSITION::LEFT_DIAGONAL) continue;
//				else
//				{
//					_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.bottom),Vector2(_tile[_currentIndex].rc.right,_tile[_currentIndex].rc.top)),LINEAR_VALUE_TYPE::DOWN });
//					curr = 0;
//
//				}
//
//				break;
//			case DRAW_LINE_POSITION::RIGHT_DIAGONAL:
//				if (curr == 0)
//				{
//					_currentIndex = i;
//					curr++;
//				}
//
//				if (_tile[i + _tile[0].tileX + 3].linePos == DRAW_LINE_POSITION::RIGHT_DIAGONAL) continue;
//				else
//				{
//					_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::DOWN });
//					curr = 0;
//
//				}
//
//				break;
//			case DRAW_LINE_POSITION::PLATFORM:
//				if (curr == 0)
//				{
//					_currentIndex = i;
//					curr++;
//				}
//
//				if (_tile[i + 1].linePos == DRAW_LINE_POSITION::PLATFORM) continue;
//				else
//				{
//					_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)),LINEAR_VALUE_TYPE::DOWN });
//					curr = 0;
//
//				}
//
//				break;
//			default:
//				_currentIndex = 0;
//				curr = 0;
//				break;
//			}
//		}
//	}



