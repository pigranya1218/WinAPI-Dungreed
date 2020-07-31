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
	IMAGE_MANAGER->addFrameImage("MAIN_SCENE/BIRD", L"resources/images/MainScene/bird.png", 8, 1);
	
	// ��� �� SCENE_MANAGER�� ���
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->changeScene("MAIN");	

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
