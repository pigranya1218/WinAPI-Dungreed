#include "SpikeBall.h"
#include "stdafx.h"

void SpikeBall::init()
{
	//�Ǽ����� Ÿ��
	_itemCode = 0x0310B;
	_img = IMAGE_MANAGER->findImage("SpikeBall");
	_iconImg = IMAGE_MANAGER->findImage("SpikeBall");
	
	//�Ǽ����� �ɼ�
	_addStat.criticalChance = 1;
	_addStat.defense = 1;

	_itemName = L"���� ��";
	_displayInfos.push_back(L"���谡 ������ ���� ���� ����");
	_displayText = L"\"���谡�� ������ ���鼭 ������ ȥ���ش�.\"";
	_x = _y = 0;
	_elapsedTime = 0;
	//�Ǽ����� ����
	_price = 600;

	_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������
}

void SpikeBall::release()
{
}

void SpikeBall::update(Player* player, float const elapsedTime)
{
	_angle += 2.233f * elapsedTime;
	_elapsedTime += elapsedTime;
	if (_angle > PI2) 
	{
		_angle -= PI2;
	}
	if (_elapsedTime > 0.4) // 0.4�ʸ��� �������� �ʱ�ȭ
	{
		_elapsedTime = 0;
		_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������
	}

	_x = cosf(_angle) * 110;
	_y = -sinf(_angle) * 110;
	Vector2 playerPos = player->getPosition();

	FloatCircle* attackCircle;
	attackCircle = new FloatCircle;
	attackCircle->origin = Vector2(playerPos.x + _x, playerPos.y + _y);
	attackCircle->size = 40;
	attackCircle->startRadian = 0;
	attackCircle->endRadian = PI2;

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(_attackCode);
	attackInfo->madeByWeapon = false;
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = 5;
	attackInfo->maxDamage = 10;
	attackInfo->knockBack = 5;

	player->attack(attackCircle, attackInfo);

	delete attackCircle;
	delete attackInfo;
}

void SpikeBall::frontRender(Player* player)
{
}

void SpikeBall::backRender(Player* player)
{
	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + _x;
	renderPos.y = renderPos.y + _y;
	_img->setScale(4);
	_img->render(CAMERA->getRelativeV2(renderPos), false);
	Vector2 size = Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4);
	
}
