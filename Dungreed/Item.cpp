#include "Item.h"

Item::Item(Vector2 pos, DIRECTION direction, ITEM_TYPE type):_itemPosX(pos.x), _itemPosY(pos.y)
{
}

void Item::update()
{
	_width = _ptMouse.x - _itemPosX;
	_height = _ptMouse.y - _itemPosY;
	_angle = atan2(_width, _height);
	_itemImg->setAngle(_angle);
}

void Item::render()
{
	_itemImg->setScale(_imgScale);
}

