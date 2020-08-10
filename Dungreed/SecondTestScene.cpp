#include "stdafx.h"
#include "SecondTestScene.h"
#include "SampleStage.h"

HRESULT SecondTestScene::init()
{
	_stage=new SampleStage;
	_stage->init();
	return S_OK;
}

void SecondTestScene::release()
{
}

void SecondTestScene::update()
{
	_stage->update();
}

void SecondTestScene::render()
{
	_stage->render();
}
