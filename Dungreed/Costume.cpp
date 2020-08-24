#include "Costume.h"

void Costume::release()
{
	_ani->release();
	delete _ani;
}

void Costume::update(float elaspedTime)
{
	if (_ani->isPlay())
	{
		_ani->frameUpdate(elaspedTime);
	}
	for (int i = 0; i < _effects.size();)
	{
		if (_effects[i].remainTime <= 0)
		{
			_effects.erase(_effects.begin() + i);
		}
		else
		{
			_effects[i].remainTime = max(0, _effects[i].remainTime - elaspedTime);
			i++;
		}
	}
}

void Costume::render(Vector2 pos, DIRECTION dir, bool isAlpha)
{
	Image* _effectImg = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/JUMP_EFFECT");
	for (int i = 0; i < _effects.size(); i++)
	{
		_effectImg->setScale(4);
		_effectImg->setAlpha(_effects[i].remainTime / 0.5);
		_effectImg->render(CAMERA->getRelativeV2(_effects[i].pos), (_effects[i].dir == DIRECTION::LEFT));
	}

	// 확대
	_img->setScale(4);
	if (isAlpha)
	{
		_img->setAlpha(0.4);
	}
	// 상태에 따른 애니메이션 사용 여부 
	switch (_imgState)
	{
	case PLAYER_STATE::IDLE:
	case PLAYER_STATE::MOVE:
	{
		_img->aniRender(pos, _ani, (dir == DIRECTION::LEFT));
	}
	break;
	case PLAYER_STATE::JUMP:
	case PLAYER_STATE::DIE:
	{
		_img->render(pos, (dir == DIRECTION::LEFT));
	}
	break;
	}
}

void Costume::setSprite(PLAYER_STATE state, bool isForced)
{
	if (_imgState == state && !isForced) return;

	switch (state)
	{
	case PLAYER_STATE::IDLE:
	{
		_imgState = PLAYER_STATE::IDLE;

		_img = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/IDLE");
		_ani->stop();
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setDefPlayFrame(false, true);
		_ani->start();
	}
	break;
	case PLAYER_STATE::MOVE:
	{
		_imgState = PLAYER_STATE::MOVE;

		_img = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/MOVE");
		_ani->stop();
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setDefPlayFrame(false, true);
		_ani->start();
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		_imgState = PLAYER_STATE::JUMP;

		_img = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/JUMP");
		_ani->stop();
	}
	break;
	case PLAYER_STATE::DIE:
	{
		_imgState = PLAYER_STATE::DIE;

		_img = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/DIE");
		_ani->stop();
	}
	break;
	}
}

void Costume::dashEffect(Vector2 pos, DIRECTION dir)
{
	tagDashEffect dashEffect;
	dashEffect.pos = pos;
	dashEffect.remainTime = 0.5;
	dashEffect.dir = dir;
	_effects.push_back(dashEffect);
}
