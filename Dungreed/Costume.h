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
	string _costumeName;	// 이미지를 찾기 위해 활용되는 코스튬별 이름
	wstring _costumeTitle;	// 코스튬의 한글 이름
	wstring _costumeSummary;	// 코스튬 개요
	wstring _costumeDetails;	// 코스튬 상세내용

	PlayerStat _baseStat; // 기본 스탯
	PlayerStat _differStat; // 코스튬별 다른 스탯

	Image* _img;
	Animation* _ani;
	PLAYER_STATE _imgState;

	vector<Item*> _specialAbility; // 특수 능력

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float elaspedTime) = 0;
	virtual void render(Vector2 pos, DIRECTION dir, bool isAlpha) = 0;
	virtual void setSprite(PLAYER_STATE state, bool isForced) = 0;	// 애니메이션을 재생시킬 함수
	
	PlayerStat const getBaseStat() { return _baseStat + _differStat; } // 코스튬의 기본 스탯을 반환
	vector<Item*> getSpecialAbility() { return _specialAbility; } // 코스튬의 특수 능력 반환
	string getCostumeName() { return _costumeName; }
	wstring getTitle() { return _costumeTitle; }
	wstring getSummary() { return _costumeSummary; }
	wstring getDetails() { return _costumeDetails; }
	virtual PlayerStat* getDifferStat() { return &_differStat; } //코스튬의 변동 스탯 반환
};

