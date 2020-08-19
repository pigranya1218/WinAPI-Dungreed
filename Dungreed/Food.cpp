#include "stdafx.h"
#include "Food.h"

FOOD_RANK Food::getRank()
{
	if (_foodCode & static_cast<int>(FOOD_RANK::NORMAL) == static_cast<int>(FOOD_RANK::NORMAL))
	{
		return FOOD_RANK::NORMAL;
	}
	if (_foodCode & static_cast<int>(FOOD_RANK::RARE) == static_cast<int>(FOOD_RANK::RARE))
	{
		return FOOD_RANK::RARE;
	}
}
