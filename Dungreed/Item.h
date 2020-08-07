#pragma once
#include "GameObject.h"

class Item : public GameObject
{
private:
protected:
	string _name;					//�̸�
	string _explanation;			//������ ����
	//string _itemDefualtOption;	//������ �⺻�ɼ�		�÷��̾� ���� ���� ���� ����ȯ
	//string _itemRandomOption;		//������ �����ɼ�		�÷��̾� ���� ���� ���� ����ȯ

	Image* _itemImg;				//������ �̹���
	Animation* _itemAni;			//������ �ִϸ��̼�
	Animation* _itemEffect;			//������ ����Ʈ
	float _imgScale = 3;			//ũ��
	float _radius;					//������ ���� ������
	float _itemPosX, _itemPosY;		//���� x, y ��ġ
public:
	//Item();
	//Item(Vector2 pos, DIRECTION direction, ITEM_TYPE type) :_itemPosX(pos.x), _itemPosY(pos.y) {}

	void init();
	void update();
	void release();
	void render();
	//bool attack(Player* ganeObject);
};

