#pragma once
#include "Object.h"

class Player;

class DoorObject : public Object
{
private:
	struct tagOpenEffect
	{
		Vector2 pos;
		float remainTime;
	};


private:
	Image* _img;
	Player* _player;

	DIRECTION _direction; // ��� ���� ������

	Animation* _ani;

	bool _isOpen;
	vector<tagOpenEffect> _openTextures;

	float _delayTime;

private:

public:
	void init(Vector2 pos, DIRECTION direction); // �¿� ���� ���� �� ���, ���� ���� ���� | ���
	virtual void release() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;

	void setOpen(bool isOpen);
	bool isOpen() { return _isOpen; }

};

