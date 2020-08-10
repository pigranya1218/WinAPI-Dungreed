#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:	
	string		_imageName;		// 이미지 이름
	Image*		_img;			// 사용할 이미지
	Vector2		_startPos;		// 불릿 시작 위치
	Animation*	_ani;			// 프레임 사용 애니메이션

	float		_speed;			// 속도
	float		_range;			// 사정거리
	float		_angle;			// 각도
	float		_scale;			// 스케일

	bool		_isFire;		// 트루면 발사시작함
	bool		_isDelete;		// 불릿을 삭제해도 됌

public:
	void init(string imageName, const Vector2& pos, float angle, float speed, float range, float scale);
	void release();
	void update();
	void render();

	void setFire(bool isFire) { _isFire = isFire; }
	bool getDelete() const { return _isDelete; }

	bool rangeOverCheck();
};

