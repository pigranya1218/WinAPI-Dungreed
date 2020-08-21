#include "stdafx.h"
#include "Food.h"

FOOD_RANK Food::getRank()
{
	if (_foodCode / 256 == static_cast<int>(FOOD_RANK::NORMAL) / 256)
	{
		return FOOD_RANK::NORMAL;
	}
	if (_foodCode / 256 == static_cast<int>(FOOD_RANK::RARE) / 256)
	{
		return FOOD_RANK::RARE;
	}
}
