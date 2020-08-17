#include "SpikeBall.h"
#include "stdafx.h"

void SpikeBall::init()
{
	//악세서리 타입
	_itemCode = 0x0310B;
	_img = IMAGE_MANAGER->findImage("SpikeBall");
	_iconImg = IMAGE_MANAGER->findImage("SpikeBall");
	//악세서리 옵션
	_addStat.criticalChance = 1;
	_addStat.defense = 1;
	
	_itemName = L"뾰족 공";
	_displayInfos.push_back(L"모험가 주위를 돌며 적을 공격");
	_displayText = L"\"모험가의 주위를 돌면서 적들을 혼내준다.\"";
	_x = _y = 0;

	
	//악세서리 가격
	_price = 600;

}

void SpikeBall::release()
{
}

void SpikeBall::update(Player* player, float const elapsedTime)
{
	_angle += 2.233f*elapsedTime;
}

void SpikeBall::frontRender(Player* player)
{
}

void SpikeBall::backRender(Player* player)
{
	_x = cosf(_angle) * 110;
	_y = -sinf(_angle) * 110;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + _x;
	renderPos.y = renderPos.y + _y;
	_img->setScale(4);
	_img->render(CAMERA->getRelativeV2(renderPos), false);
	Vector2 size = Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4);
	_crash = rectMakePivot(Vector2(renderPos), size, PIVOT::CENTER);
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_crash));
}



void SpikeBall::displayInfo()
{
}

void SpikeBall::attack(Player* player)
{
}

void SpikeBall::attack(FloatRect * rect, AttackInfo * info)
{
}

void SpikeBall::attack(FloatCircle * circle, AttackInfo * info)
{
}

void SpikeBall::attack(Projectile * projectile, AttackInfo * info)
{
}

void SpikeBall::getHit(Vector2 const position)
{
}

void SpikeBall::equip(Player* player)
{
}
