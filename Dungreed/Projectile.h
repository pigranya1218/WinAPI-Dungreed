#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
protected:
	OBJECT_TEAM _team;
	Image* _img;								//이미지
	int _bulletCount;							//장탄수
	float _shootTermTime;						//발사텀
	float _reloadTime;							//재장전 시간
	FloatRect _bulletRect;						//총알 렉트
	Vector2 _position;
	float _angle;								//발사각
	Animation* _ani;
public:
	void init();
	virtual void fire();
	virtual void move();
};