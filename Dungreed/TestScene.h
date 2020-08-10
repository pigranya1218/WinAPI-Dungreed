#pragma once
#include "GameNode.h"
#include "GameObject.h"


class Player;

class TestScene : public GameNode
{
private:
	Player* _player;
	
	//����
	//Synthesize(PIVOT, _pivot, rectMakePivot)
	FloatRect _ground;
	Vector2 _center;
	Vector2 _size;

	bool _mouseMove;
	POINT _lastMousePt;


public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����

	void setPlayer(Player* player) { _player = player; }
	//�浹ó��
	void moveObject(GameObject* object, Vector2 moveDir);



	//���� ��Ʈ ������
	const FloatRect getGroundRect() { return _ground; }
};

