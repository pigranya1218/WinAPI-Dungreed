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
	Vector2 renderPos = player->getPosition();
	_angle += 2.233f*elapsedTime;

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

	FloatCircle* attackCircle = new FloatCircle;
	attackCircle->origin = renderPos;
	attackCircle->size = 240;
	attackCircle->startRadian = _angle - PI * 0.28;
	attackCircle->endRadian = _angle + PI * 0.28;

	_attackDebug = FloatCircle(renderPos, 240, _angle - PI * 0.28, _angle + PI * 0.28); // forDEBUG

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 15;

	player->attack(attackCircle, attackInfo);
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
