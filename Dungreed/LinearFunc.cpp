#include "stdafx.h"
#include "LinearFunc.h"

LinearFunc::LinearFunc(Vector2 start, Vector2 end)
{
	a = (start.y - end.y) / (start.x - end.x); // x ��ȭ���� ���� y ��ȭ�� ����
	b = start.y - (start.x * a); // y ����
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
	if (differX == 0 && differY != 0) // x = b ���� ���� ����
	{
		newFunc.a = INF_A;
		newFunc.b = pointA.x;
	}
	else // y = ax + b�� ��Ÿ�� �� �ִ� ����
	{
		newFunc.a = differY / differX; // x ��ȭ���� ���� y ��ȭ�� ����
		newFunc.b = pointA.y - (pointA.x * newFunc.a); // y ����
	}
	return newFunc;
}
