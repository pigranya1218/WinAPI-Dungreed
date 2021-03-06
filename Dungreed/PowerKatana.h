#pragma once
#include "Item.h"
class PowerKatana : public Item
{

private: string _sounds[3] = { "SOUND_katana", "SOUND_katana2" ,"SOUND_katana3" };


private:
	// 공격 관련
	Image* _img;
	Image* _imgAttack;
	Image*	_effect;
	int	_minDamage;
	int _maxDamage;
	Vector2 _attackMove;
	float _baseAttackDelay; // 공격 쿨타임
	float _currAttackDelay; // 남은 공격 쿨타임
	float _attackAngle;
	float _angleOffset;
	bool _reverseMove;
	bool _drawEffect;
	bool _oneAttack;
	FloatRect _hand;
	Vector2 _handSize;
	float _width;
	float _height;

	FloatCircle _attackDebug;
public:
	virtual void init();
	virtual void update(Player* player, float const elapsedTime);
	virtual void frontRender(Player* player);

	virtual void attack(Player* player); // 플레이어가 공격버튼을 누를때 호출될 함수(공격과 상관없는 아이템이라면 빈 함수로 구현)

	virtual void equip(Player* player); // 아이템을 장착했을 때 호출될 함수, 스탯이 어떻게 바뀌어야하는지 반환

};
