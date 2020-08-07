#pragma once
#include "GameObject.h"

class Item : public GameObject
{
private:
protected:
	string _name;					//이름
	string _explanation;			//아이템 설명
	//string _itemDefualtOption;	//아이템 기본옵션		플레이어 스탯 형에 따라 형변환
	//string _itemRandomOption;		//아이템 랜덤옵션		플레이어 스탯 형에 따라 형변환

	Image* _itemImg;				//아이템 이미지
	Animation* _itemAni;			//아이템 애니메이션
	Animation* _itemEffect;			//아이템 이펙트
	ITEM_TYPE _type;
	float _imgScale = 3;			//크기
	float _radius;					//범위를 위한 반지름
	float _itemPosX, _itemPosY;		//받을 x, y 위치
	float _width, _height;			
	float _angle;					//마우스와 플레이어 위치 사이의 각도 값
public:
	//Item();
	Item(Vector2 pos, DIRECTION direction, ITEM_TYPE type);

	//void init();
	void update();
	//void release();
	void render();
	//bool attack(Player* ganeObject);
};

