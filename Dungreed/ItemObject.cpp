#include "ItemObject.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Item.h"

void ItemObject::init(Item* item, Vector2 pos, float power, float radian)
{
	_objectCode = 0x0020;
	_item = item;
	_position = pos;
	_size = Vector2(20, 20);
	_power = power;
	_radian = radian;
	_force = Vector2(0, 0);
	_player = _objectMgr->getPlayer();
	_active = true;
}

void ItemObject::release()
{
}

void ItemObject::update(float elapsedTime)
{
	Vector2 moveDir(0, 0);
	_force.y += 80 * elapsedTime;
	moveDir.x += cosf(_radian) * _power * elapsedTime;
	moveDir.y += -sinf(_radian) * _power * elapsedTime + _force.y;
	_objectMgr->moveTo(this, moveDir);
	if (_isStand)
	{
		_force.y = 0;
		_power = 0;
	}

	// 플레이어와 충돌 처리
	FloatRect playerRc = FloatRect(_player->getPosition(), _player->getSize(), PIVOT::CENTER);
	FloatRect goldRc = FloatRect(_position, _size, PIVOT::CENTER);
	if (FloatRect::intersect(playerRc, goldRc))
	{
		if (_player->collisionItem(_item))
		{
			_active = false;
		}
	}
}

void ItemObject::render()
{
	_item->getIconImg()->setScale(4);
	_item->getIconImg()->render(_position);
}
