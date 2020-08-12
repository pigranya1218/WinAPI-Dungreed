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

Vector2 LinearFunc::getStart()
{
	if (a == INF_A)
	{
		return Vector2(b, start);
	}
	else
	{
		return Vector2(start, getY(start));
	}
}

Vector2 LinearFunc::getEnd()
{
	if (a == INF_A)
	{
		return Vector2(b, end);
	}
	else
	{
		return Vector2(end, getY(end));
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
		newFunc.start = start.y;
		newFunc.end = end.y;
	}
	else
	{
		newFunc.a = differY / differX; // x ��ȭ���� ���� y ��ȭ�� ����
		newFunc.b = start.y - (start.x * newFunc.a); // y ����
		newFunc.start = start.x;
		newFunc.end = end.x;
	}
	return newFunc;
}
