#pragma once
#include "Projectile.h"

//class ProjectileManager;

class GunBullet : public Projectile
{
private:
	Image* _img;								//이미지
	int _bulletCount;							//장탄수
	float _shootTermTime;						//발사텀
	float _reloadTime;							//재장전 시간
	FloatRect _bulletRect;						//총알 렉트
	Vector2 _position;
	float _angle;								//발사각
	Animation* _ani;
	//vector<>
public:
	virtual void init(int itemType, Vector2 pos);
	virtual void release();
	virtual void update(float timeElapsed);
	virtual void render();
	void fire(Vector2 const pos, float const angle);
	void move();
};

