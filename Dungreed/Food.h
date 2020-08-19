#pragma once
#include "PlayerStat.h"

enum class FOOD_RANK : int
{
	NORMAL = 0x0100,
	RARE = 0x0200
};

class Food
{
protected:
	int _foodCode;

	Image* _img;
	string _name;
	int	_price;

	PlayerStat _addStat;  // �������ν� �����Ǵ� ����
	PlayerStat _onceStat; // ���� �� �ܹ߼����� ����Ǵ� ����(ü�� ȸ��, ������)

public:
	Image* getImage() { return _img; }
	string getName() { return _name; }
	int	getPrice() { return _price; }
	
	PlayerStat getAddStat() { return _addStat; }
	PlayerStat getOnceStat() { return _onceStat; }

	FOOD_RANK getRank();
};

