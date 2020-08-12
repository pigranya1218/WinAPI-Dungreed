#pragma once
#include "Projectile.h"

#define PI 3.124159f

class PlayerBullet
{
private:
	Image* _bulletImg;								//이미지
	int _bulletCount;							//장탄수
	float _shootTermTime;						//발사텀
	float _reloadTime;							//재장전 시간
	float _angle;								//발사각
	Animation* _ani;
	Image* _effect01;
	Image* _effect02;
	int _ObjectType;							//임시
	Vector2 _position;
	
	char _buffer[128];
public:
	void init(Vector2 pos, float angle);
	void update(float const elapsedTime);
	void release();
	void render();
	virtual void fire();
	virtual void move();

};

