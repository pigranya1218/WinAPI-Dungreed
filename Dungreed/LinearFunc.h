#pragma once

enum class LINEAR_VALUE_TYPE
{
	UP, // ������ ���� ����
	ON, // ���� ���� ��������
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
	SynthesizePublic(float, a, A); // x ����
	SynthesizePublic(float, b, B); // y ����

public:
	LinearFunc() {}
	LinearFunc(float a, float b) :a(a), b(b) {}
	LinearFunc(Vector2 start, Vector2 end);

	LINEAR_VALUE_TYPE getValueType(float x, float y);
	
	float getX(float y) { return (y - b) / a; }
	float getY(float x) { return a * x + b; }

public:
	static LinearFunc getLinearFuncFromPoints(Vector2 start, Vector2 end);
};
