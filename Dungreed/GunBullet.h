#pragma once
#include "Projectile.h"

//class ProjectileManager;

class GunBullet : public Projectile
{
private:
	Image* _img;								//�̹���
	int _bulletCount;							//��ź��
	float _shootTermTime;						//�߻���
	float _reloadTime;							//������ �ð�
	FloatRect _bulletRect;						//�Ѿ� ��Ʈ
	Vector2 _position;
	float _angle;								//�߻簢
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

