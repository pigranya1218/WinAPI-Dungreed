#pragma once
#include "Item.h"
class babyGreenBat : public Item
{
private:
	Image* _img;
	Animation* _ani;

	Vector2 _renderPos;
	Vector2 _batPos;
	
	DIRECTION _direction;
	
	float _baseAttackDelay;   // ���� ��Ÿ��
	float _currAttackDelay;   // ���� ���� ��Ÿ��
	int _maxBullet;           // �ִ� �Ѿ� ����
	int _currBullet;          // ���� �Ѿ� ����
	float _baseReloadDelay;   // ������ ��Ÿ��
	float _currReloadDelay;   // ���� ������ ��Ÿ��	

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);	
	virtual void attack(Player* player);
	
};

