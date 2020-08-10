#pragma once
#include "GameNode.h"
#include "GameObject.h"

class Player;
class Item;
class Matchlock;

class TestScene : public GameNode
{
private:
	Player* _player;
	Item* _item;
	Matchlock* _matchlock;

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
	void setItem(Item* item) { _item = item; }
	//�浹ó��
	void moveObject(GameObject* object, Vector2 moveDir);

	//���� ��Ʈ ������
	const FloatRect getGroundRect() { return _ground; }
};

