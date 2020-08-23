#include "watCher.h"

void watCher::init()
{
	//�Ǽ����� Ÿ��
	_itemCode = 0x0310D;
	_iconImg = IMAGE_MANAGER->findImage("Watcher");
	
	//�Ǽ����� �ɼ�

	_itemName = L"�ֽ���";
	_displayInfos.push_back(L"���԰� ������ ���� ���Ÿ� ���� ���");
	_displayText = L"\"�ֺ��� ��� ���Ÿ� ����ü���� ������ش�.\"";

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



	//�Ǽ����� ����
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
	
}

void watCher::backRender(Player * player)
{	
	
	
	_img->setScale(4);	
	_img->aniRender(CAMERA->getRelativeV2(Vector2(_renderPos)), _ani, false);
	
}

bool watCher::isHit(Projectile* projectile)
{
	// �ǰ� ���� �˻�
	FloatRect accRc = FloatRect(_renderPos, Vector2(40, 40), PIVOT::CENTER);
	FloatRect attackRc = FloatRect(projectile->getPosition(), projectile->getSize(), PIVOT::CENTER);

	if (!FloatRect::intersect(accRc, attackRc)) // �簢���� �簢���� �浹 �˻� �Լ�
	{
		return false; // �ǰ� ������ �ƴϹǷ� �ǰ� ó�� ����
	}
	else
	{
		return true; // �ǰ�������
	}
}
