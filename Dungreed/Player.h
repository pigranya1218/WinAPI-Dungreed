#pragma once
#include "GameObject.h"

enum PLAYER_STATE
{
	IDLE, 
	MOVE, //점프 중이 아닌 경우에만
	JUMP, //점프 중일 때도 좌 우 이동은 가능하지만 점프 상태는 그대로
	DIE	  //사망
};

class Player : public GameObject
{
private:
	Animation* _ani;
	Image* _img;
	PLAYER_STATE _state;

	//스탯
	float _satiety;			//포만감
	float _power;			//위력 (위력 수치 1당 피해량 1% 상승)
	float _damage;			//무기 공격력 //몬스터에게 들어가는 데미지 = (무기공격력 * (1+위력/100))
	float _trueDamage;		//고정 데미지
	float _criticalChance;	//크리티컬 확률
	float _criticalDamage;	//크리티컬 데미지
	float _dashDamage;		//대쉬 공격력
	float _toughness;		//강인함
	float _defense;			//방어력
	float _block;			//막기
	float _evasion;			//회피
	float _attackSpeed;		//공격속도
	float _moveSpeed;		//이동속도


public:
	Player() {};
	~Player() {};

	void move(Vector2 moveDir);

	void init();
	void release();
	void update();
	void render();
};

