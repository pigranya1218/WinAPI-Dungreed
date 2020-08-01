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

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	GameNode::init(true);

	// ��� �̹��� IMAGE_MANAGER�� ���
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

	// ** ENEMY

	

	// ��� �� SCENE_MANAGER�� ���
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->changeScene("MAIN");	

	TIME_MANAGER->update();

	return S_OK;
}

//�޸� ����
void playGround::release()
{
	GameNode::release();
}

//����
void playGround::update()
{
	GameNode::update();

	SCENE_MANAGER->update();
	DEBUG_MANAGER->update();
}

//�׸��� ����
void playGround::render()
{	
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		SCENE_MANAGER->render();		
	}
	D2D_RENDERER->endRender();
}
