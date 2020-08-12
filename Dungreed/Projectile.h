#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
protected:
	OBJECT_TEAM _team;
	Image* _img;								//�̹���
	int _bulletCount;							//��ź��
	float _shootTermTime;						//�߻���
	float _reloadTime;							//������ �ð�
	FloatRect _bulletRect;						//�Ѿ� ��Ʈ
	Vector2 _position;
	float _angle;								//�߻簢
	Animation* _ani;
public:
	void init();
	virtual void fire();
	virtual void move();
};