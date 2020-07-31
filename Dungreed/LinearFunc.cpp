#include "stdafx.h"
#include "LinearFunc.h"

LinearFunc::LinearFunc(Vector2 start, Vector2 end)
{
	a = (start.y - end.y) / (start.x - end.x); // x 변화량에 대한 y 변화량 비율
	b = start.y - (start.x * a); // y 절편
}

LINEAR_VALUE_TYPE LinearFunc::getValueType(float x, float y)
{
	if (a != INF_A)
	{
		float result = y - (a * x + b);
		if (FLOAT_EQUAL(result, 0))
		{
			return LINEAR_VALUE_TYPE::ON;
		}
		else if (result < 0)
		{
			return LINEAR_VALUE_TYPE::UP;
		}
		else
		{
			return LINEAR_VALUE_TYPE::DOWN;
		}
	}
	else
	{
		if (x == b)
		{
			return LINEAR_VALUE_TYPE::ON;
		}
		else if (x < b)
		{
			return LINEAR_VALUE_TYPE::LEFT;
		}
		else
		{
			return LINEAR_VALUE_TYPE::RIGHT;
		}
	}
	
}

LinearFunc LinearFunc::getLinearFuncFromPoints(Vector2 start, Vector2 end)
{
	LinearFunc newFunc;
	float differY = (start.y - end.y);
	float differX = (start.x - end.x);
	if (differX == 0 && differY != 0)
	{
		newFunc.a = INF_A;
		newFunc.b = start.x;
	}
	else
	{
		newFunc.a = differY / differX; // x 변화량에 대한 y 변화량 비율
		newFunc.b = start.y - (start.x * newFunc.a); // y 절편
	}
	return newFunc;
}
