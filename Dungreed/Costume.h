#pragma once
#include "PlayerStat.h"
#include "stdafx.h"

class Item;

enum class COSTUME_TYPE : int
{
	BASE = 0,
	METAL_PLATE,
	ALICE,
	RED_LOTUS,
	PICKAX,
	END
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
	string _costumeName;	// �̹����� ã�� ���� Ȱ��Ǵ� �ڽ�Ƭ�� �̸�
	wstring _costumeTitle;	// �ڽ�Ƭ�� �ѱ� �̸�
	wstring _costumeSummary;	// �ڽ�Ƭ ����
	wstring _costumeDetails;	// �ڽ�Ƭ �󼼳���

	PlayerStat _baseStat; // �⺻ ����
	PlayerStat _differStat; // �ڽ�Ƭ�� �ٸ� ����

	Image* _img;
	Animation* _ani;
	PLAYER_STATE _imgState;

	vector<Item*> _specialAbility; // Ư�� �ɷ�

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float elaspedTime) = 0;
	virtual void render(Vector2 pos, DIRECTION dir, bool isAlpha) = 0;
	virtual void setSprite(PLAYER_STATE state, bool isForced) = 0;	// �ִϸ��̼��� �����ų �Լ�
	
	PlayerStat const getBaseStat() { return _baseStat + _differStat; } // �ڽ�Ƭ�� �⺻ ������ ��ȯ
	vector<Item*> getSpecialAbility() { return _specialAbility; } // �ڽ�Ƭ�� Ư�� �ɷ� ��ȯ
	string getCostumeName() { return _costumeName; }
	wstring getTitle() { return _costumeTitle; }
	wstring getSummary() { return _costumeSummary; }
	wstring getDetails() { return _costumeDetails; }
	virtual PlayerStat* getDifferStat() { return &_differStat; } //�ڽ�Ƭ�� ���� ���� ��ȯ
};

