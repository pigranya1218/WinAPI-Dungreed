#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:	
	string		_imageName;		// �̹��� �̸�
	Image*		_img;			// ����� �̹���
	Vector2		_startPos;		// �Ҹ� ���� ��ġ
	Animation*	_ani;			// ������ ��� �ִϸ��̼�

	float		_speed;			// �ӵ�
	float		_range;			// �����Ÿ�
	float		_angle;			// ����
	float		_scale;			// ������

	bool		_isFire;		// Ʈ��� �߻������
	bool		_isDelete;		// �Ҹ��� �����ص� ��

public:
	void init(string imageName, const Vector2& pos, float angle, float speed, float range, float scale);
	void release();
	void update();
	void render();

	void setFire(bool isFire) { _isFire = isFire; }
	bool getDelete() const { return _isDelete; }

	bool rangeOverCheck();
};

