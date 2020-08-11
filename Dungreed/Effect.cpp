#include "stdafx.h"
#include "Effect.h"

Effect::Effect()
	: _effectImage(nullptr),
	_effectAnimation(nullptr),
	_isRunning(false)
{
	_position = Vector2(0, 0);
	_size = Vector2(0, 0);
}

Effect::~Effect()
{
}

void Effect::init(Image * effectImage, int fps)
{
	if (!effectImage) return;

	_effectImage = effectImage;
	_isRunning = false;

	//이펙트 애니메이션이 없으면 생성해라
	if (!_effectAnimation) _effectAnimation = new Animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(),
		_effectImage->getMaxFrameX(), _effectImage->getMaxFrameY());
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();
}

void Effect::release()
{
	_effectImage = nullptr;
	SAFE_DELETE(_effectAnimation);
}

void Effect::update(float elapsedTime)
{
	//이펙트 애니메이션 실행 변수가 false면 실행하지 마라
	if (!_isRunning) return;

	_effectAnimation->frameUpdate(elapsedTime);

	if (!_effectAnimation->isPlay()) killEffect();
}

void Effect::render()
{
	if (!_isRunning) return;

	_effectImage->setScale(_scale);
	if (_size.x != 0 && _size.y != 0)
	{
		_effectImage->setAngle(_angle);
		CAMERA->aniRender(_effectImage, _position, _size, _effectAnimation);
		//_effectImage->aniRender(_position, _size, _effectAnimation);

	}
	else
	{
		_effectImage->setAngle(_angle);
		CAMERA->aniRender(_effectImage, _position, _effectAnimation);
		//_effectImage->aniRender(_position, _effectAnimation);
	}
}

void Effect::startEffect(Vector2 pos, float angle)
{
	_isRunning = true;
	_effectAnimation->start();
	_position = pos;
	_size = Vector2(0, 0);
	_angle = angle;
}

void Effect::startEffect(Vector2 pos, Vector2 size, float angle)
{
	_isRunning = true;
	_effectAnimation->start();
	_position = pos;
	_size = size;
	_angle = angle;
}

void Effect::killEffect()
{
	_isRunning = false;
}
