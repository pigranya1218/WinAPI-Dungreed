#include "SilverBullet.h"

void SilverBullet::init()
{
	//�Ǽ����� Ÿ��
	_itemCode = 0x03312;
	_iconImg = IMAGE_MANAGER->findImage("SilverBullet");

	//�Ǽ����� �ɼ�
	
	_itemName = L"�� źȯ";
	_displayInfos.push_back(L"�Ѿ��� ���� ����");
	_displayText = L"\"�� ���� ������ �ذ�å ������ ����.\"";
	
	//�Ǽ����� ����
	_price = 3200;
}

void SilverBullet::attack(Player * player, Projectile * projectile, AttackInfo * info)
{
	projectile->setUseEnemyCollision(false);
}
