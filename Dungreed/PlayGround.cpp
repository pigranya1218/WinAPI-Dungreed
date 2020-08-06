#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"
#include "TestScene.h"

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
	// * MAIN SCENE
	IMAGE_MANAGER->addImage("MAIN_SCENE/LOGO", L"resources/images/MainScene/MainLogo.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/COPYRIGHT", L"resources/images/MainScene/Copyright.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/TEAM_LOGO", L"resources/images/MainScene/TeamLogo.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/PLAY_ON", L"resources/images/MainScene/PlayOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/PLAY_OFF", L"resources/images/MainScene/PlayOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/OPTION_ON", L"resources/images/MainScene/OptionOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/OPTION_OFF", L"resources/images/MainScene/OptionOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/EXIT_ON", L"resources/images/MainScene/ExitOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/EXIT_OFF", L"resources/images/MainScene/ExitOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/FRONT_CLOUD", L"resources/images/MainScene/FrontCloud.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/BACK_CLOUD", L"resources/images/MainScene/BackCloud.png");
	IMAGE_MANAGER->addFrameImage("MAIN_SCENE/BIRD", L"resources/images/MainScene/bird.png", 8, 1);
	
	// * STAGE SCENE
	// ** VILLIGE

	// ** DUNGEON

	// ** PLAYER
	IMAGE_MANAGER->addFrameImage("PLAYER/IDLE", L"resources/images/characters/player/player_idle.png", 5, 1);
	IMAGE_MANAGER->addFrameImage("PLAYER/RUN", L"resources/images/characters/player/player_run.png", 8, 1);
	IMAGE_MANAGER->addImage("PLAYER/JUMP", L"resources/images/characters/player/player_jump.png");
	IMAGE_MANAGER->addImage("PLAYER/DIE", L"resources/images/characters/player/player_die.png");

	// ** ENEMY

	

	// 모든 씬 SCENE_MANAGER에 등록
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("TEST", new TestScene);
	SCENE_MANAGER->changeScene("TEST");	

	TIME_MANAGER->update();

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

}

//그리기 전용
void playGround::render()
{	
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		SCENE_MANAGER->render();		
	}
	D2D_RENDERER->endRender();
}
