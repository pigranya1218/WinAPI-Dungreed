#include "Niflheim.h"

void Niflheim::init(const Vector2& pos, DIRECTION direction)
{
	_ani = new Animation;

	setState(ENEMY_STATE::IDLE);

	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2);

	_scale = 4;

	for (int i = 0; i < 4; i++)
	{
		ZeroMemory(&_pillar[i], sizeof(_pillar[i]));
		_pillar[i].ani = new Animation;

		_pillar[i].img = IMAGE_MANAGER->findImage("Niflheim/Pillar");
		_pillar[i].ani->init(_pillar[i].img->getWidth(), _pillar[i].img->getHeight(), _pillar[i].img->getMaxFrameX(), _pillar[i].img->getMaxFrameY());
		_pillar[i].ani->setDefPlayFrame(false, false);
		_pillar[i].ani->setFPS(15);
		_pillar[i].ani->start();

		_pillar[i].angle = PI / 2 * i;

		_pillar[i].position = _position;
		_pillar[i].position.x += cosf(_pillar[i].angle) * 100;
		_pillar[i].position.y -= sinf(_pillar[i].angle) * 100;
	}

	_active = true;
}

void Niflheim::release()
{

}

void Niflheim::update(float const timeElapsed)
{
	_ani->frameUpdate(timeElapsed);
	for (int i = 0; i < 4; i++)
	{
		_pillar[i].angle += timeElapsed * 2;
		if (_pillar[i].angle > PI2) _pillar[i].angle = 0;
		_pillar[i].ani->frameUpdate(timeElapsed);

		_pillar[i].position = _position;
		_pillar[i].position.x += cosf(_pillar[i].angle) * 200;
		_pillar[i].position.y -= sinf(_pillar[i].angle) * 200;
	}
}

void Niflheim::render()
{
	_img->setScale(_scale);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	for (int i = 0; i < 4; i++)
	{
		_pillar[i].img->setScale(4);
		_pillar[i].img->setAngle((_pillar[i].angle * (180 / PI)) + 90);
		//_pillar[i].img->setAnglePos(Vector2((_pillar[i].img->getFrameSize().x * 4) * 0.5f, (_pillar[i].img->getFrameSize().y * 4) * 0.5f));
		_pillar[i].img->aniRender(CAMERA->getRelativeV2(_pillar[i].position), _pillar[i].ani);
	}
}

void Niflheim::setState(ENEMY_STATE state)
{
	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_img = IMAGE_MANAGER->findImage("Niflheim/Idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(15);
			_ani->start();
		}
		break;
	case ENEMY_STATE::MOVE:
		break;
	case ENEMY_STATE::ATTACK:
		break;
	case ENEMY_STATE::SKILL:
		break;
	case ENEMY_STATE::DIE:
		break;
	default:
		break;
	}

}
