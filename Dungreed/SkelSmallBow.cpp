#include "stdafx.h"
#include "EnemyManager.h"
#include "SkelSmallBow.h"

void SkelSmallBow::init(const Vector2 & pos, DIRECTION direction)
{
	// 애니메이션 할당
	_ani = new Animation;
	_weaponAni = new Animation;

	// 상태 초기화
	setState(ENEMY_STATE::IDLE);

	// 에너미 관련 변수 초기화
	_position = pos;
	_direction = direction;
	_scale = 4;
	_detectRange = 300;

	// 충돌 사이즈 및 렉트 초기화
	_size = Vector2(_img->getFrameSize().x, _img->getFrameSize().y);
	_size = _size * _scale;
	_rect = rectMakePivot(_position, _size, PIVOT::CENTER);

	// 공격 관련 초기화
	ZeroMemory(&_attack, sizeof(_attack));
	_attack.delay = 3;

	// 플레이어 감지 변수 초기화
	_isDetect = 0;
}

void SkelSmallBow::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SkelSmallBow::update(float const timeElapsed)
{
	_weaponPos = _position;
	_weaponPos.x += ((bool)_direction) ? _weaponImg->getFrameSize().x : -_weaponImg->getFrameSize().x;
	_weaponPos.y += 10;

	if (!_isDetect)
	{
		_isDetect = _enemyManager->detectPlayer(this, _detectRange);
	}

	switch (_state)
	{
		case ENEMY_STATE::IDLE:
		{
			if (_isDetect)
			{
				const Vector2 playerPos = _enemyManager->getPlayerPos();
				_direction = playerPos.x > _position.x ? DIRECTION::RIGHT : DIRECTION::LEFT;

				_attack.angle = getAngle(_position.x, _position.y, playerPos.x, playerPos.y) * (180 / PI) + 360;
				if (_attack.angle > 360) _attack.angle -= 360;

				if (_attack.update(timeElapsed))
				{
					setState(ENEMY_STATE::ATTACK);
				}
			}
			break;
		}
		case ENEMY_STATE::ATTACK:
		{
			if (!_weaponAni->isPlay())
			{
				setState(ENEMY_STATE::IDLE);
			}

			_weaponAni->frameUpdate(timeElapsed);
			break;
		}
		case ENEMY_STATE::DIE:
		{
			break;
		}
	}
}

void SkelSmallBow::render()
{
	// 무기 각도
	float drawAngle = _attack.angle;
	if (_direction == DIRECTION::LEFT)
	{
		drawAngle = 180 - _attack.angle;
		if (drawAngle < 0) drawAngle += 360;
	}
	// 무기 좌표
	Vector2 drawPos = _position;
	//drawPos.x += (_direction == DIRECTION::LEFT) ? -(_weaponImg->getFrameSize().x) : (_weaponImg->getFrameSize().x);
	
	//drawPos.y += 10;

	_img->setScale(_scale);
	_weaponImg->setScale(_scale);
	_weaponImg->setAngle(drawAngle);	
	
	if (_state == ENEMY_STATE::ATTACK)
	{

		drawPos.x -= (_direction == DIRECTION::LEFT) ? _weaponImg->getFrameSize().x * 0.30f*_scale : -(_weaponImg->getFrameSize().x*0.3f*_scale);
		drawPos.y += 10;


		_img->render(CAMERA->getRelativeV2(_position), (_direction == DIRECTION::LEFT));
		_weaponImg->aniRender(CAMERA->getRelativeV2(drawPos), _weaponAni, (_direction == DIRECTION::LEFT));
	}
	else
	{
		drawPos.x -= (_direction == DIRECTION::LEFT) ? _weaponImg->getWidth()*0.30f*_scale : -(_weaponImg->getWidth()*0.3f*_scale);
		drawPos.y += 10;


		_weaponImg->setAnglePos(Vector2((0.4f * _weaponImg->getWidth()), _weaponImg->getHeight() * 0.5f));
		_img->render(CAMERA->getRelativeV2(_position), (_direction == DIRECTION::LEFT));
		_weaponImg->render(CAMERA->getRelativeV2(drawPos), (_direction == DIRECTION::LEFT));
	}

}

void SkelSmallBow::setState(ENEMY_STATE state)
{
	_state = state;

	// 상태에 따른 애니메이션 설정
	switch (state)
	{
		case ENEMY_STATE::IDLE:
		{
			_ani->stop();
			_weaponAni->stop();

			_img = IMAGE_MANAGER->findImage("Skel/Small/Idle");
			_weaponImg = IMAGE_MANAGER->findImage("Skel/Small/Bow_Idle");

			break;
		}
		case ENEMY_STATE::ATTACK:
		{
			_weaponAni->stop();
			_ani->stop();

			_img = IMAGE_MANAGER->findImage("Skel/Small/Idle");
			_weaponImg = IMAGE_MANAGER->findImage("Skel/Small/Bow_Attack");
			_weaponAni->init(_weaponImg->getWidth(), _weaponImg->getHeight(), _weaponImg->getMaxFrameX(), _weaponImg->getMaxFrameY());
			_weaponAni->setDefPlayFrame(false, false);
			_weaponAni->setFPS(5);
			_weaponAni->start();

			break;
		}
		case ENEMY_STATE::DIE:
		{
			break;
		}
	}
}
