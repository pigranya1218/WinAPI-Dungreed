#include "stdafx.h"
#include "BrokenObject.h"
#include "ObjectManager.h"
#include "ParticleObject.h"
#include "GoldObject.h"
#include "HpFairyObject.h"

Image* BrokenObject::getImage()
{
	Image* result = nullptr;
	switch (_objectCode)
	{
	case 0x0000: // 드럼통
	{
		_fileName = "DRUM";
	}
	break;
	case 0x0001: // 박스
	{
		_fileName = "BOX";
	}
	break;
	case 0x0002: // 큰 박스
	{
		_fileName = "BIG_BOX";
	}
	break;
	}
	return IMAGE_MANAGER->findImage("OBJECT/BROKEN/" + _fileName);;
}

Vector2 BrokenObject::getObjectSize()
{
	switch (_objectCode)
	{
	case 0x0000: // 드럼통
	{
		return Vector2(40, 50);
	}
	break;
	case 0x0001: // 박스
	{
		return Vector2(50, 50);
	}
	break;
	case 0x0002: // 큰 박스
	{
		return Vector2(80, 60);
	}
	break;
	}
}

void BrokenObject::respawnParticle()
{
	int particleCount = 0;
	switch (_objectCode)
	{
	case 0x0000: // 드럼통
	{
		particleCount = 5;
	}
	break;
	case 0x0001: // 박스
	{
		particleCount = 7;
	}
	break;
	case 0x0002: // 큰 박스
	{
		particleCount = 6;
	}
	break;
	}

	for (int i = 0; i < particleCount; i++)
	{
		Image* particleImage = IMAGE_MANAGER->findImage("OBJECT/PARTICLE/" + _fileName + "_" + to_string(i));
		Vector2 pos = Vector2(RANDOM->getFromFloatTo(_position.x - _size.x, _position.x + _size.x), RANDOM->getFromFloatTo(_position.y, _position.y - _size.y));
		float power = RANDOM->getFromFloatTo(700, 1300);
		float radian = RANDOM->getFromFloatTo(0.2 * PI, 0.8 * PI);

		ParticleObject* object = new ParticleObject;
		object->setObjectManager(_objectMgr);
		object->init(particleImage, pos, power, radian);
		_objectMgr->pushObject(object);
	}
}

void BrokenObject::respawnGold()
{
	for (int i = 0; i < 5; i++)
	{
		Vector2 pos = Vector2(RANDOM->getFromFloatTo(_position.x - _size.x, _position.x + _size.x), RANDOM->getFromFloatTo(_position.y, _position.y - _size.y));
		float power = RANDOM->getFromFloatTo(600, 800);
		float radian = RANDOM->getFromFloatTo(0.2 * PI, 0.8 * PI);

		GoldObject* object = new GoldObject;
		object->setObjectManager(_objectMgr);
		object->init(10, pos, power, radian);
		_objectMgr->pushObject(object);
	}

}

void BrokenObject::respawnHpFairy()
{
	Vector2 pos = Vector2(_position.x, _position.y - _size.y);

	HpFairyObject* object = new HpFairyObject;
	object->setObjectManager(_objectMgr);
	object->init(10, pos);
	_objectMgr->pushObject(object);
}

void BrokenObject::init(int objectCode, Vector2 pos)
{
	_objectCode = objectCode;
	_active = true;

	_img = getImage();
	_position = pos;
	_size = getObjectSize();
}

void BrokenObject::update(float elapsedTime)
{
	_force.y += elapsedTime * 80;
	_objectMgr->moveTo(this, _force);
	if (_isStand)
	{
		_force.y = 0;
	}
}

void BrokenObject::render()
{
	_img->setScale(4);
	_img->render(CAMERA->getRelativeV2(_position));
	D2D_RENDERER->drawRectangle(FloatRect(CAMERA->getRelativeV2(_position), _size, PIVOT::CENTER), D2D1::ColorF::Enum::Black, 1, 1);
}

bool BrokenObject::hitEffect(FloatRect* rect, AttackInfo* info)
{
	_active = false;
	respawnParticle();
	int randomCount = RANDOM->getInt(100);
	if (randomCount < 80)
	{
		respawnGold();
	}
	else
	{
		respawnHpFairy();
	}
	return true;
}

bool BrokenObject::hitEffect(FloatCircle* circle, AttackInfo* info)
{
	_active = false;
	respawnParticle();
	int randomCount = RANDOM->getInt(100);
	if (randomCount < 80)
	{
		respawnGold();
	}
	else
	{
		respawnHpFairy();
	}
	return true;
}

bool BrokenObject::hitEffect(Projectile* projectile)
{
	_active = false;
	respawnParticle();
	int randomCount = RANDOM->getInt(100);
	if (randomCount < 80)
	{
		respawnGold();
	}
	else
	{
		respawnHpFairy();
	}
	return true;
}
