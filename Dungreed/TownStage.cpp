#include "stdafx.h"
#include "TownStage.h"

HRESULT TownStage::init()
{
	IMAGE_MANAGER->findImage("Town_BGL");
	IMAGE_MANAGER->findImage("Town_BG");
	IMAGE_MANAGER->findImage("Town_BG2");
	IMAGE_MANAGER->findImage("Town_Floor");

	return S_OK;
}

void TownStage::release()
{
}

void TownStage::update()
{
	
}

void TownStage::render()
{
	_camera.render(IMAGE_MANAGER->findImage("Town_BGL"), Vector2(500, 500));
}
