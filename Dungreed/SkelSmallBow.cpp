#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelSmallBow.h"

void SkelSmallBow::init(const Vector2 & pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::ATTACK);

	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	_size = Vector2(_img->getFrameSize().x, _img->getFrameSize().y);
	_size = _size * _scale;

	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3;

	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	_isDetect = 0;
}

void SkelSmallBow::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelSmallBow::update(float const timeElapsed)
{
	_ani->frameUpdate(timeElapsed);
}

void SkelSmallBow::render()
{
	_img->setScale(_scale);
	_img->aniRender(_position, _ani, !(bool)_direction);
}

void SkelSmallBow::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
	case ENEMY_STATE::IDLE:
	{
		/*_ani->stop();
		_img = IMAGE_MANAGER->findImage("Skel/Magician_Ice/Idle");
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, true);
		_ani->setFPS(10);
		_ani->start();*/

		break;
	}
	case ENEMY_STATE::ATTACK:
	{
		_ani->stop();
		_img = IMAGE_MANAGER->findImage("test");
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, true);
		_ani->setFPS(10);
		_ani->start();

		break;
	}
	case ENEMY_STATE::DIE:
	{
		break;
	}
	}
}
