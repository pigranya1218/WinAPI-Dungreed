#include "SeeriProjectile.h"
#include "ProjectileManager.h"
#include "Player.h"

void SeeriProjectile::init(const string imgKey, const string collisionEffect, const Vector2 & drawSize, const Vector2 & collsionRectSize, const Vector2 & effectSize, const Vector2 & force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate, bool useGravity, bool collsionGround, bool collsionPlatForm, bool collsionEnemy)
{
	float elapseXY;

	_angleRadian = angleRadian;
	_force = force;

	_maxTime = maxTime;
	_count = 0;

	_img = IMAGE_MANAGER->findImage(imgKey);

	if (useAni)
	{
		elapseXY = fabsf(_img->getFrameSize().x - _img->getFrameSize().y);

		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(aniFps);
		_ani->setDefPlayFrame(false, isAniLoop);
		_ani->start();
	}

	_useAni = useAni;
	_useRotate = useRotate;
	_useGravity = useGravity;

	_collsionGround = collsionGround;
	_collisionPlatForm = collsionPlatForm;
	_collisionEffect = collisionEffect;
	_useCollsionEnemy = collsionEnemy;

	_drawSize = drawSize;
	_size = collsionRectSize;
	_effectSize = effectSize;

	_gravity = Vector2(0, 4000);

	_active = true;
	_Delay = 0.2f;
	_length = _img->getFrameSize().x * 1.0f;

	_timeCount = 0;
}

void SeeriProjectile::release()
{

	Projectile::release();

	if (_useAni)
	{
		_ani->release();
		SAFE_DELETE(_ani);
	}
}

void SeeriProjectile::update(float elapsedTime)
{
	if (_Delay > 0)
	{
		_Delay = max(0, _Delay - elapsedTime);
		_position.y -= 300* elapsedTime;		
	}
	_enemyPos = _projectileMgr->getEnemyPos(_position);
	_timeCount += elapsedTime;	
	Vector2 moveDir(0, 0);
	
	if (_Delay == 0)
	{
		// �߷� ����
		if (_useGravity)
		{
			_force.y += _gravity.y * elapsedTime * ((_angleRadian > PI) ? (1) : (-1));
		}

		// ����ü���� ���ʹ̱����� ����
		float guidedAngleRadian = atan2f(-(CAMERA->getAbsoluteY(_enemyPos.y) - _position.y), (CAMERA->getAbsoluteX(_enemyPos.x) - _position.x)) + PI2;
		if (guidedAngleRadian > PI2)
		{
			guidedAngleRadian -= PI2;
		}



		if (_timeCount <= 0.3f)
		{
			moveDir.x += cosf(_angleRadian) * _force.x * elapsedTime;
			moveDir.y -= sinf(_angleRadian) * _force.y * elapsedTime;
		}

		if (_timeCount > 0.3f)
		{
			if (_angleRadian <= guidedAngleRadian)
			{
				if ((guidedAngleRadian - _angleRadian) > (_angleRadian + (PI2 - guidedAngleRadian)))
				{
					//_angleRadian -= 2.f * elapsedTime;
					if (_angleRadian < 0.f)
					{
						_angleRadian = PI2;
					}
					_angleRadian -= 3.f * elapsedTime;
					//_angleRadian -= 0.1f;
				}
				else
				{
					_angleRadian += 3.f * elapsedTime;
					//_angleRadian += 2.f * elapsedTime;
					//_angleRadian += 0.1f;
				}
			}
			else
			{
				if ((_angleRadian - guidedAngleRadian) < ((PI2 - _angleRadian) + guidedAngleRadian))
				{
					//_angleRadian -= 2.f * elapsedTime;
					_angleRadian -= 3.f * elapsedTime;
					//_angleRadian -= 0.1f;
				}
				else
				{
					//_angleRadian += 2.f * elapsedTime;
					if (_angleRadian >= PI2)
					{
						_angleRadian = 0;
					}
					//_angleRadian += 0.1f;
					_angleRadian += 3.f * elapsedTime;
				}
			}

			// �̵�
			moveDir.x += cosf(_angleRadian) * _force.x * elapsedTime;
			moveDir.y -= sinf(_angleRadian) * _force.y * elapsedTime;
		}
	}
	Vector2 lastDir = _position;
	_projectileMgr->moveTo(this, moveDir, _collsionGround, _collisionPlatForm);
	Vector2 currDir = _position;

	Vector2 effectPos = _position;
	effectPos.x += cosf(_angleRadian) * _length;
	effectPos.y += -sinf(_angleRadian) * _length;
	_img->setAngle(_angleRadian*2);

	if (lastDir + moveDir != currDir)
	{
		float angleDegree = _angleRadian * (180.0f / PI);
		EFFECT_MANAGER->play(_collisionEffect, effectPos, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));
		_active = false;
	}
	

	// Ÿ�Կ� ���� �浹 �˻�
	if (_info->team == OBJECT_TEAM::PLAYER)
	{
		// ENEMY���� �浹 �˻�
		if (_projectileMgr->checkEnemyCollision(this, _useCollsionEnemy)) // ���� �浹�ߴٸ�
		{
			float angleDegree = _angleRadian * (180.0f / PI);
			EFFECT_MANAGER->play(_collisionEffect, effectPos, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));

			if (_useCollsionEnemy)
			{
				_active = false;
			}
			return;
		}
	}
	else
	{
		// TODO: PLAYER���� �浹 �˻�
		if (_projectileMgr->checkPlayerCollision(this, true))
		{
			_active = false;
			return;
		}

	}

	// ���ӽð��� �Ѿ��
	_count += elapsedTime;
	if (_count >= _maxTime)
	{
		float angleDegree = _angleRadian * (180.0f / PI);
		EFFECT_MANAGER->play(_collisionEffect, effectPos, _effectSize, ((_useRotate) ? (angleDegree) : (0.0f)));

		_active = false;
	}

	// �ִϸ��̼� ��� �� ������ ���
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}

void SeeriProjectile::render()
{
	if (_useRotate)
	{
		_img->setAngle(_angleRadian * (180 / PI));
	}
	if (_useAni)
	{
		_img->aniRender(CAMERA->getRelativeV2(_position), _drawSize, _ani);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}
	else
	{
		
	
		_img->render(CAMERA->getRelativeV2(_position), _drawSize);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(FloatRect(_position, _size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, 5);
	}
}

void SeeriProjectile::aniUpdate(float const elapsedTime)
{
	if (_useAni)
	{
		_ani->frameUpdate(elapsedTime);
	}
}