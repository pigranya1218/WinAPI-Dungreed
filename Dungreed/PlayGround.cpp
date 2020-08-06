#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"

#include <string>

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	GameNode::init(true);

	// 모든 이미지 IMAGE_MANAGER에 등록
	// * COMMON IMAGE

	IMAGE_MANAGER->addFrameImage("smapleTile", L"resources/images/Map/tileAtlas.png");

	// ** MOUSE CURSOR
	IMAGE_MANAGER->addImage("CURSOR_BASIC", L"resources/images/common/cursor/BasicCursor.png");
	IMAGE_MANAGER->addImage("CURSOR_SHOOTING", L"resources/images/common/cursor/ShootingCursor2.png");

	// ** CONFIG
	IMAGE_MANAGER->addImage("OPTION_HEADER", L"resources/images/common/option/OptionBase2.png");
	IMAGE_MANAGER->addImage("OPTION_BG", L"resources/images/common/option/ScrollRect.png");

	// ** BUTTON
	IMAGE_MANAGER->addImage("BUTTON_EXIT", L"resources/images/common/button/FullWindowExitButton.png");
	IMAGE_MANAGER->addImage("BUTTON_EXIT_SELECTED", L"resources/images/common/button/FullWindowExitButton_Selected.png");

	// * MAIN SCENE
	IMAGE_MANAGER->addImage("MAIN_SCENE/LOGO", L"resources/images/mainScene/MainLogo.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/COPYRIGHT", L"resources/images/mainScene/Copyright.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/TEAM_LOGO", L"resources/images/mainScene/TeamLogo.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/PLAY_ON", L"resources/images/mainScene/PlayOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/PLAY_OFF", L"resources/images/mainScene/PlayOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/OPTION_ON", L"resources/images/mainScene/OptionOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/OPTION_OFF", L"resources/images/mainScene/OptionOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/EXIT_ON", L"resources/images/mainScene/ExitOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/EXIT_OFF", L"resources/images/mainScene/ExitOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/FRONT_CLOUD", L"resources/images/mainScene/FrontCloud.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/BACK_CLOUD", L"resources/images/mainScene/BackCloud.png");
	IMAGE_MANAGER->addFrameImage("MAIN_SCENE/BIRD", L"resources/images/mainScene/bird.png", 8, 1);
	
	// * STAGE SCENE
	// ** VILLIGE

	// ** DUNGEON

	// ** ENEMY

	

	// 모든 씬 SCENE_MANAGER에 등록
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->changeScene("MAIN");	

	TIME_MANAGER->update();

	CONFIG_MANAGER->init();
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	GameNode::release();
}

//연산
void playGround::update()
{
	GameNode::update();

	SCENE_MANAGER->update();
	DEBUG_MANAGER->update();
	CONFIG_MANAGER->update();
}

//그리기 전용
void playGround::render()
{	
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		SCENE_MANAGER->render();
		CONFIG_MANAGER->render();

	}
	D2D_RENDERER->endRender();
}
