#pragma once
#include "Enemy.h"
#include <vector>

#define HANDSPEED 600
#define PARTICLEMAX 30
#define SIZEMAX 5

enum class BELIAL_STATE : int
{
	SHOOTING,
	SWORD,
	LASER
};

class Belial : public Enemy
{
private:
	tagMoveInfo _moving;
	tagShootingInfo _shooting;
	tagAttackInfo _attacking;

	struct tagHandInfo
	{
	};
	struct tagLaser
	{
		Animation*		_ani;
		Image*			_img;			// 이미지
		string			_imageName;		// 이미지 이름

		Vector2 _laserPosition;
		Vector2 _laserSize;
		string  _imgName;
	};
	tagHandInfo _handR;
	tagHandInfo _handL;
	BELIAL_STATE _Belial_Attack;
	vector<tagLaser> _vlaser;
	bool _isAttack;
	int _replayCount;




public:
	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};


