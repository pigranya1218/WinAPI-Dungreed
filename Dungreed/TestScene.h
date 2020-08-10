#pragma once
#include "GameNode.h"
#include "GameObject.h"


class Player;
class Weapon;
class TestScene : public GameNode
{
private:
	Player* _player;
	Camera _camera;

	//지형
	//Synthesize(PIVOT, _pivot, rectMakePivot)
	FloatRect _ground;
	Vector2 _center;
	Vector2 _size;

	bool _mouseMove;
	POINT _lastMousePt;

	Image* _weapon;
	Image* _item;




public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용

	void setPlayer(Player* player) { _player = player; }
	//충돌처리
	void moveObject(GameObject* object, Vector2 moveDir);



	//지형 렉트 접근자
	const FloatRect getGroundRect() { return _ground; }
};

