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

	
	_addStat.yGravity = -1800;
	_addStat.xGravity = -1000;

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

