#pragma once
#include "PlayerStat.h"
#include "stdafx.h"

enum class COSTUME_TYPE : int
{
	BASE = 0,
	METAL_PLATE,
	PICKAX,
	ALICE,
	RED_LOTUS
};

enum class PLAYER_STATE : int
{
	IDLE = 0, // USE ANI
	MOVE, // USE ANI
	JUMP, // NO ANI
	DIE // NO ANI
};

class Costume
{
protected:
	string _costumeName; // �̹����� ã�� ���� Ȱ��Ǵ� �ڽ�Ƭ�� �̸�

	PlayerStat _baseStat; // �� �ڽ�Ƭ�� �⺻ ����

	Image* _img;
	Animation* _ani;
	PLAYER_STATE _imgState;

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float elaspedTime) = 0;
	virtual void render(Vector2 pos, DIRECTION dir) = 0;
	virtual void setSprite(PLAYER_STATE state, bool isForced) = 0;	// �ִϸ��̼��� �����ų �Լ�
	
	PlayerStat const getBaseStat() { return _baseStat; } // �ڽ�Ƭ�� �⺻ ������ ��ȯ
};

