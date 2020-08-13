#include "miniEarth.h"
#include "stdafx.h"

void miniEarth::init()
{
	//�Ǽ����� Ÿ��
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("MiniEarth0");

	//�Ǽ����� �ɼ�
	
	x = y = 0;
	_ani = new Animation;
	_ani->start();

	//�Ǽ����� ����
	_price = 600;
}

void miniEarth::release()
{
}

void miniEarth::update(Player * player, float const elapsedTime)
{
	_angle += 0.023f;
	_ani->frameUpdate(elapsedTime);
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(10);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
}

void miniEarth::backRender(Player * player)
{
	x = cosf(_angle) * 50;
	y = -sinf(_angle) * 50;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + x;
	renderPos.y = renderPos.y + y;
	_img->setScale(4);
	_img->aniRender(Vector2(renderPos), _ani, false);
	Vector2 size = Vector2(_img->getFrameSize().x*2 , _img->getFrameSize().y *2);
	_crash = rectMakePivot(Vector2(renderPos.x, renderPos.y+20), size, PIVOT::CENTER);
	D2D_RENDERER->drawRectangle(_crash);
}

void miniEarth::frontRender(Player * player)
{
}

void miniEarth::displayInfo()
{
}

void miniEarth::attack(Player * player)
{
}

void miniEarth::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void miniEarth::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void miniEarth::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void miniEarth::getHit(Vector2 const position)
{
}

PlayerStat miniEarth::equip()
{
	return PlayerStat();
}
