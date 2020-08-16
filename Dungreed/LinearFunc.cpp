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
		else if (result <= 0)
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
		if (FLOAT_EQUAL(x, b))
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

LinearFunc LinearFunc::getLinearFuncFromPoints(Vector2 pointA, Vector2 pointB, Vector2 rangeX, Vector2 rangeY)
{
	LinearFunc newFunc;
	newFunc.start = pointA;
	newFunc.end = pointB;
	newFunc.rangeX = rangeX;
	newFunc.rangeY = rangeY;

	float differY = (pointA.y - pointB.y);
	float differX = (pointA.x - pointB.x);
	if (differX == 0 && differY != 0) // x = b 꼴의 수직 선분
	{
		newFunc.a = INF_A;
		newFunc.b = pointA.x;
	}
	else // y = ax + b로 나타낼 수 있는 선분
	{
		newFunc.a = differY / differX; // x 변화량에 대한 y 변화량 비율
		newFunc.b = pointA.y - (pointA.x * newFunc.a); // y 절편
	}
	return newFunc;
}
