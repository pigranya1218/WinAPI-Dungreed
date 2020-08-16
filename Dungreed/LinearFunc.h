#pragma once
#include "stdafx.h"

enum class LINEAR_VALUE_TYPE
{
	ON, // ���а� �ε���
	UP, // ������ ���� ����
	DOWN, // ������ �Ʒ��� ����
	LEFT, // ������ ���ʿ� ���� (x = 100 ���� �Լ� �ÿ����� ���)
	RIGHT // ������ �����ʿ� ���� (x = 100 ���� �Լ� �ÿ����� ���)
};

// 1�� �Լ�, ������ �������� ���Ʒ� ��� ��ġ�ϴ��� �Ǵ��ϴ� �޼��� ����
class LinearFunc
{
public:
	static const int INF_A = 987654321;
public:
	SynthesizePublic(Vector2, start, Start); // X�� ����
	SynthesizePublic(Vector2, end, End); // X�� ����
	SynthesizePublic(Vector2, rangeX, RangeX); // X�� ����
	SynthesizePublic(Vector2, rangeY, RangeY); // Y�� ����
	SynthesizePublic(float, a, A); // x ����, a = INF_A��� x = b ���� �����Լ��̴�
	SynthesizePublic(float, b, B); // y ����, a = INF_A��� x = b ���� �����Լ��̴�

public:
	LinearFunc() {}
	LinearFunc(Vector2 start, Vector2 end);

	LINEAR_VALUE_TYPE getValueType(float x, float y);
	
	float getX(float y) { return (y - b) / a; }
	float getY(float x) { return a * x + b; }

public:
	// start, end : ������ ���ϱ� ���� �� ��, rangeX : X�� ����, rangeY : Y�� ����
	static LinearFunc getLinearFuncFromPoints(Vector2 pointA, Vector2 pointB, Vector2 rangeX, Vector2 rangeY);
};;
