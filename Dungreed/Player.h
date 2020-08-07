#pragma once
#include "GameObject.h"

class TestScene;

//애니메이션 재생용 (상태패턴 아님)
enum PLAYER_ANIMATION
{
	DEFALT,	//점프나 사망과 같이 애니렌더를 사용하지 않는 경우.
	IDLE, 
	MOVE	//점프 중이 아닌 경우에만
	//JUMP	//점프 중일 때도 좌 우 이동은 가능하지만 점프 상태는 그대로
	//DIE	  //사망
};

class Player : public GameObject
{
private:
	TestScene* _testScene;
	Animation* _ani;
	Image* _img;
	PLAYER_ANIMATION _setAni;
	Synthesize(DIRECTION, _direction, Direction)

	Vector2 _moveDir;

	//점프
	int _jumpCount;			//점프 횟수
	float _jumpPower;		//점프력
	float _gravity;			//중력가속도
	float _jumpSpeed;		//점프속도
	bool _isJump;			//점프 처리(지면과 떨어진 상태)

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
	void setAni(PLAYER_ANIMATION setAni);

	void init();
	void release();
	void update();
	void render();

	void setTestScene(TestScene* testScene) { _testScene = testScene; }

	//플레이어의 position 설정자
	//void setPosition()
	//플레이어의 position 접근자
	Vector2 getPosition() { return _position; }
};

