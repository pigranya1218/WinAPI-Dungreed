#include "watCher.h"

void watCher::init()
{
	//악세서리 타입
	_itemCode = 0x0310D;
	_iconImg = IMAGE_MANAGER->findImage("Watcher");
	
	//악세서리 옵션

	_itemName = L"주시자";
	_displayInfos.push_back(L"모함가 주위를 돌며 원거리 공격 방어");
	_displayText = L"\"주변에 닿는 원거리 투사체들을 방어해준다.\"";

	_addStat.evasion = 5;

	_radius = 0;
	_fspeed = 0;
	_anglePos.x = _anglePos.y =0;
	_img = IMAGE_MANAGER->findImage("Watcher0");	
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(7);
	_ani->start();
	_setitem = false;



	//악세서리 가격
	_price = 1200;
}

void watCher::release()
{

}

void watCher::update(Player * player, float const elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown('8'))
	{
		_setitem = false;
		
	}
	if (KEY_MANAGER->isOnceKeyDown('9'))
	{
		_setitem = true;
		
	}
	
	if (!_setitem)
	{
		_radius = 85;
		_img = IMAGE_MANAGER->findImage("Watcher0");
		_angle -= 2.743f*elapsedTime;
		
	}
	else
	{
		_radius = 130;
		_img = IMAGE_MANAGER->findImage("Watcher1");
		_angle -= 2.962f*elapsedTime;
		
	}

	_ani->frameUpdate(elapsedTime);
	_anglePos.x = cosf(_angle) * _radius;
	_anglePos.y = -sinf(_angle) * _radius;
	_renderPos = player->getPosition();
	_renderPos.x = _renderPos.x + _anglePos.x + 2;
	_renderPos.y = _renderPos.y + _anglePos.y - 22;
	Vector2 size = Vector2(_img->getFrameSize().x * 2, _img->getFrameSize().y * 2);
	_crash = rectMakePivot(Vector2(_renderPos.x, _renderPos.y + 25), size, PIVOT::CENTER);	
}

void watCher::backRender(Player * player)
{	
	
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_crash));
	_img->setScale(4);	
	_img->aniRender(CAMERA->getRelativeV2(Vector2(_renderPos)), _ani, false);
	
}

void watCher::frontRender(Player * player)

{
}

void watCher::displayInfo()
{
}

void watCher::attack(Player * player)
{
}

void watCher::attack(FloatRect * rect, AttackInfo * info)
{
}

void watCher::attack(FloatCircle * circle, AttackInfo * info)
{
}

void watCher::attack(Projectile * projectile, AttackInfo * info)
{
}

void watCher::getHit(Vector2 const position)
{
}

void watCher::equip(Player* player)
{
}
