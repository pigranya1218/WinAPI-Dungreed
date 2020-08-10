#include "stdafx.h"
#include "SampleStage.h"


HRESULT SampleStage::init()
{

	_mapImage = IMAGE_MANAGER->findImage("sampleTile");
	mapLoad();
	return S_OK;
}

void SampleStage::release()
{
}

void SampleStage::update()
{

}

void SampleStage::render()
{
	

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		_mapImage->setScale(2);
		_mapImage->frameRender(_tile[i].rc.getCenter(), _tile[i].tileFrameX, _tile[i].tileFrameY);
	}
	IMAGE_MANAGER->findImage("Town_BGL")->setScale(5);
	_camera.render(IMAGE_MANAGER->findImage("Town_BGL"), Vector2(WINSIZEX / 2, WINSIZEY / 2));
	IMAGE_MANAGER->findImage("Town_BG")->setScale(5);
	_camera.render(IMAGE_MANAGER->findImage("Town_BG"), Vector2(WINSIZEX / 2, WINSIZEY / 2+200));
	IMAGE_MANAGER->findImage("Town_BG2")->setScale(5);
	_camera.render(IMAGE_MANAGER->findImage("Town_BG2"), Vector2(WINSIZEX / 2, WINSIZEY / 2+200));

}

void SampleStage::mapLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("stage.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile , sizeof(tagTileMap)*TILEX*TILEY, &read, NULL);



	CloseHandle(file);
}
