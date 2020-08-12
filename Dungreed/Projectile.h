#pragma once
#include "GameObject.h"


class Projectile : public GameObject
{
private:
	Image* _img;								//이미지
	int _bulletCount;							//장탄수
	float _shootTermTime;						//발사텀
	float _reloadTime;							//재장전 시간
	float _angle;								//발사각
	Animation* _ani;
	Image* _effect01;
	Image* _effect02;
	int _ObjectType;							//임시
public:
	void init();
	virtual void fire();
	virtual void move();
};