#include "AliceCos.h"
#include "AliceAbility.h"

void AliceCos::init()
{
	//코스튬 이름 설정
	_costumeName = "ALICE";

	AliceAbility* ability = new AliceAbility;
	ability->init();
	_specialAbility.push_back(ability);

	//코스튬 설명창에 보여줄 내용들
	_costumeTitle = L"앨리스";
	_costumeSummary = L"토끼는 보이지 않고, 멋진 표적이 가득해";
	_costumeDetails = L"원시: 일정 반경 안에 적이 있다면 위력이 -20 감소합니다.";

	_ani = new Animation;

	//현재 재생할 이미지
	setSprite(PLAYER_STATE::IDLE, true);

	//변동 스탯
	_differStat.maxHp = -30;
	_differStat.power = 40;

	//베이스 스탯
	_baseStat.maxHp = 80;
	_baseStat.maxJumpCount = 1;
	_baseStat.maxDashCount = 5;
	_baseStat.dashCoolTime = 1.5f;
	_baseStat.maxSatiety = 100;
	_baseStat.power = 0;
	_baseStat.minDamage = 0; //0 ~ 4
	_baseStat.maxDamage = 0; //0 ~ 4
	_baseStat.trueDamage = 0;
	_baseStat.criticalChance = 10;
	_baseStat.criticalDamage = 100; // + 100%
	_baseStat.toughness = 0;
	_baseStat.defense = 0;
	_baseStat.block = 0;
	_baseStat.evasion = 0;
	_baseStat.attackSpeed = 0;
	_baseStat.reloadSpeed = 0; // --
	_baseStat.moveSpeed = 350;
	_baseStat.dashXPower = 1700;
	_baseStat.dashYPower = 1500;
	_baseStat.jumpPower = 1400;
	_baseStat.xGravity = 4000;
	_baseStat.yGravity = 4000;
}

