#include "MetalBoots.h"

void MetalBoots::init()
{
	//�Ǽ����� Ÿ��
	_itemCode = 0x03210;
	_iconImg = IMAGE_MANAGER->findImage("MetalBoots");
	

	//�Ǽ����� �ɼ�	
	_itemName = L"��ö��ȭ";
	_displayInfos.push_back(L"������ ���ظ� ������");
	_displayText = L"\"�ٴ� �κп� ��ö�� ������ϴ�.\"";

	_addStat.defense = 3;
	//�Ǽ����� ����
	_price = 1800;

}

void MetalBoots::release()
{
}

void MetalBoots::update(Player * player, float const elapsedTime)
{
	
}

void MetalBoots::backRender(Player * player)
{
}

void MetalBoots::frontRender(Player * player)
{
}



