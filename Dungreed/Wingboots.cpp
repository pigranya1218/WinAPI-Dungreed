#include "Wingboots.h"

void Wingboots::init()
{
	//�Ǽ����� Ÿ��
	_itemCode = 0x03211;
	_iconImg = IMAGE_MANAGER->findImage("Wingboots");

	//�Ǽ����� �ɼ�

	_itemName = L"�� ����";
	_displayInfos.push_back(L"���� ��������");
	_displayText = L"\"�߰����� ���� ���������ϴ�.\"";

	
	_addStat.jumpPower = 500;
	_addStat.dashYPower = 300;
	_addStat.dashXPower = 300;
	



	//�Ǽ����� ����
	_price = 1200;
}

void Wingboots::release()
{
}

void Wingboots::update(Player * player, float const elapsedTime)
{
}

void Wingboots::backRender(Player * player)
{
}

void Wingboots::frontRender(Player * player)
{
}

void Wingboots::displayInfo()
{
}

void Wingboots::attack(Player * player)
{
}

void Wingboots::attack(FloatRect * rect, AttackInfo * info)
{
}

void Wingboots::attack(FloatCircle * circle, AttackInfo * info)
{
}

void Wingboots::attack(Projectile * projectile, AttackInfo * info)
{
}

void Wingboots::getHit(Vector2 const position)
{
}

void Wingboots::equip(Player * player)
{
}
