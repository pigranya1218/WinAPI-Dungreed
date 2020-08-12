#pragma once
#include "Projectile.h"

#define PI 3.124159f

class PlayerBullet
{
private:
	Image* _bulletImg;								//�̹���
	int _bulletCount;							//��ź��
	float _shootTermTime;						//�߻���
	float _reloadTime;							//������ �ð�
	float _angle;								//�߻簢
	Animation* _ani;
	Image* _effect01;
	Image* _effect02;
	int _ObjectType;							//�ӽ�
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

