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
	SynthesizePublic(float, start, Start); // x�� ����, a = INF_A��� y�� ���� ��
	SynthesizePublic(float, end, End); // x�� ��, a = INF_A��� y�� �� ��
	SynthesizePublic(float, a, A); // x ����, a = INF_A��� x = b ���� �����Լ��̴�
	SynthesizePublic(float, b, B); // y ����, a = INF_A��� x = b ���� �����Լ��̴�

public:
	LinearFunc() {}
	LinearFunc(Vector2 start, Vector2 end);

	LINEAR_VALUE_TYPE getValueType(float x, float y);
	
	float getX(float y) { return (y - b) / a; }
	float getY(float x) { return a * x + b; }
	Vector2 getStart();
	Vector2 getEnd();

public:
	static LinearFunc getLinearFuncFromPoints(Vector2 start, Vector2 end);
};
