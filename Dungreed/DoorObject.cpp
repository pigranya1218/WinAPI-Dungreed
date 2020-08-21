#include "stdafx.h"
#include "DoorObject.h"
#include "ObjectManager.h"
#include "Player.h"

void DoorObject::init(Vector2 pos, DIRECTION direction)
{
	_img = IMAGE_MANAGER->findImage("OBJECT/DOOR");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(20);
	_ani->setPlayFrame(0, 10, false, false);
	_ani->start();

	_position = pos;

	_direction = direction;
	switch (_direction)
	{
	case DIRECTION::LEFT:
	case DIRECTION::RIGHT:
	{
		_size = Vector2(58, 64* 4);
	}
	break;
	case DIRECTION::UP:
	case DIRECTION::DOWN:
	{
		_size = Vector2(64 * 4, 58);
	}
	break;
	}

	_active = true;
	_isOpen = false;
	_player = _objectMgr->getPlayer();
	_delayTime = 0;
}

void DoorObject::release()
{
	_ani->release();
	delete _ani;
}

void DoorObject::update(float elapsedTime)
{
	if (_isOpen)
	{
		if (!_ani->isPlay())
		{
			// 텍스쳐들 생성 및 관리
			_delayTime += elapsedTime;
			if (_delayTime > 0.05)
			{
				_delayTime = 0;
				tagOpenEffect newEffect;
				if (_direction == DIRECTION::LEFT || _direction == DIRECTION::RIGHT)
				{
					newEffect.pos = Vector2(RANDOM->getFromFloatTo(_position.x - 32, _position.x + 32), RANDOM->getFromFloatTo(_position.y - 32 * 4 + 15, _position.y + 32 * 4 - 15));

				}
				else
				{
					newEffect.pos = Vector2(RANDOM->getFromFloatTo(_position.x - 32 * 4 + 15, _position.x + 32 * 4 - 15), RANDOM->getFromFloatTo(_position.y - 32, _position.y + 32));

				}
				newEffect.remainTime = 0.6;
				_openTextures.push_back(newEffect);
			}

			int move[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
			for (int i = 0; i < _openTextures.size();)
			{
				_openTextures[i].pos.x += elapsedTime * 100 * move[static_cast<int>(_direction)][0];
				_openTextures[i].pos.y += elapsedTime * 100 * move[static_cast<int>(_direction)][1];
				_openTextures[i].remainTime -= elapsedTime;
				if (_openTextures[i].remainTime < 0)
				{
					_openTextures.erase(_openTextures.begin() + i);
				}
				else
				{
					i++;
				}
			}
		}
		else
		{
			_ani->frameUpdate(elapsedTime);
		}
	}
	else
	{
		if (!_ani->isPlay())
		{
			_ani->setPlayFrame(10, 16, false, true);
			_ani->start();
		}
		else
		{

		}
		_ani->frameUpdate(elapsedTime);
	}
}

void DoorObject::render()
{
	if (_isOpen)
	{
		if (_ani->isPlay())
		{
			if (_direction == DIRECTION::LEFT || _direction == DIRECTION::RIGHT)
			{
				_img->setAngle(-90);
			}
			if (_direction == DIRECTION::DOWN)
			{
				_img->setAngle(-180);
			}
			_img->aniRender(CAMERA->getRelativeV2(_position), Vector2(64 * 4, 64), _ani, (_direction == DIRECTION::LEFT));
		}
		else
		{
			Image* textureImg = IMAGE_MANAGER->findImage("OBJECT/DOOR_OPEN_EFFECT");
			for (int i = 0; i < _openTextures.size(); i++)
			{
				textureImg->setAlpha(0.5);
				textureImg->setScale(3);
				textureImg->render(CAMERA->getRelativeV2(_openTextures[i].pos));
			}
		}
	}
	else
	{
		if (_direction == DIRECTION::LEFT || _direction == DIRECTION::RIGHT)
		{
			_img->setAngle(-90);
		}
		if (_direction == DIRECTION::DOWN)
		{
			_img->setAngle(-180);
		}
		_img->aniRender(CAMERA->getRelativeV2(_position), Vector2(64 * 4, 64), _ani, (_direction == DIRECTION::LEFT));
	}
}

void DoorObject::setOpen(bool isOpen)
{
	if (!_isOpen && isOpen)
	{
		_ani->setPlayFrame(16, 23, false, false);
		_ani->start();
	}
	_isOpen = isOpen;

}
