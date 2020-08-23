#include "TorchObject.h"

void TorchObject::init(Vector2 pos)
{
	
	_position = pos;
	_img = IMAGE_MANAGER->findImage("Torch");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();
}

void TorchObject::release()
{
	_ani->release();
	delete _ani;
}

void TorchObject::update(float elapsedTime)
{
	_ani->frameUpdate(elapsedTime);
}

void TorchObject::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), Vector2(64 , 64), _ani);
}
