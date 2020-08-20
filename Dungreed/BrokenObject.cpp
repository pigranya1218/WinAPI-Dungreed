#include "stdafx.h"
#include "BrokenObject.h"

Image* BrokenObject::getImage()
{
	Image* result = nullptr;
	switch (_objectCode)
	{
	case 0x0000: // 드럼통
	{

	}
	break;
	case 0x0001: // 박스
	{

	}
	break;
	}
	return result;
}

int BrokenObject::getParticleObjectCode()
{
	return 0;
}

void BrokenObject::init(int objectCode, Vector2 pos)
{
	_objectCode = objectCode;
	_active = true;

	_img = getImage();
	_position = pos;
	_size = Vector2(40, 40);
}

void BrokenObject::release()
{
}

void BrokenObject::update(float elapsedTime)
{
}

void BrokenObject::render()
{
}

bool BrokenObject::hitEffect(FloatRect* rect, AttackInfo* info)
{
	_active = false;
	return true;
}

bool BrokenObject::hitEffect(FloatCircle* circle, AttackInfo* info)
{
	_active = false;
	return true;
}

bool BrokenObject::hitEffect(Projectile* projectile)
{
	_active = false;
	return true;
}
