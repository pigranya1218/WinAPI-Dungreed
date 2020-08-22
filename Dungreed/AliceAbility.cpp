#include "stdafx.h"
#include "AliceAbility.h"

void AliceAbility::init()
{
	_img = IMAGE_MANAGER->findImage("ALICE_ABILITY");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();

	_addStat.power = 0;

	_isEnemyIn = false;
}

void AliceAbility::release()
{
	_ani->release();
	delete _ani;
}

void AliceAbility::update(Player* player, float const elapsedTime)
{
	FloatCircle range = FloatCircle(player->getPosition(), 200);
	Vector2 neareastEnemyPos = player->getEnemyPos(player->getPosition());
	POINT enemyPt = { neareastEnemyPos.x, neareastEnemyPos.y };
	if (range.ptInCircle(enemyPt))
	{
		if (!_isEnemyIn)
		{
			_isEnemyIn = true;
			_img = IMAGE_MANAGER->findImage("ALICE_ABILITY_WARNING");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true); 
			_ani->start();
			_addStat.power = -20;
			player->updateAdjustStat();
		}
	}
	else
	{
		if (_isEnemyIn)
		{
			_isEnemyIn = false;
			_img = IMAGE_MANAGER->findImage("ALICE_ABILITY");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true); 
			_ani->start();
			_addStat.power = 0;
			player->updateAdjustStat();
		}
	}

	_ani->frameUpdate(elapsedTime);
}

void AliceAbility::backRender(Player* player)
{
	_img->aniRender(CAMERA->getRelativeV2(player->getPosition()), Vector2(400, 400), _ani);
}
