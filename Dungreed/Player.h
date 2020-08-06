#pragma once
#include "GameObject.h"

class TestScene;

enum PLAYER_STATE
{
	IDLE, 
	MOVE, //���� ���� �ƴ� ��쿡��
	JUMP, //���� ���� ���� �� �� �̵��� ���������� ���� ���´� �״��
	DIE	  //���
};

class Player : public GameObject
{
private:
	TestScene* _testScene;
	Animation* _ani;
	Image* _img;
	PLAYER_STATE _state;
	
	Synthesize(DIRECTION, _direction, Direction)


	//����
	float _satiety;			//������
	float _power;			//���� (���� ��ġ 1�� ���ط� 1% ���)
	float _damage;			//���� ���ݷ� //���Ϳ��� ���� ������ = (������ݷ� * (1+����/100))
	float _trueDamage;		//���� ������
	float _criticalChance;	//ũ��Ƽ�� Ȯ��
	float _criticalDamage;	//ũ��Ƽ�� ������
	float _dashDamage;		//�뽬 ���ݷ�
	float _toughness;		//������
	float _defense;			//����
	float _block;			//����
	float _evasion;			//ȸ��
	float _attackSpeed;		//���ݼӵ�
	float _moveSpeed;		//�̵��ӵ�


public:
	Player() {};
	~Player() {};

	void move(Vector2 moveDir);

	void init();
	void release();
	void update();
	void render();

	void setTestScene(TestScene* testScene) { _testScene = testScene; }
};

