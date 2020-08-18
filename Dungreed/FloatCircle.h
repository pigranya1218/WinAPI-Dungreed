#pragma once
class FloatCircle
{
public:
	Vector2 origin; // ����
	float size; // ������ ������
	float startRadian; // �߽����κ��� �̷�� ���� ���� (�̸� ���� ȣ�� ������)
	float endRadian; // �߽����κ��� �̷�� ���� ���� (�̸� ���� ȣ�� ������)

public:
	FloatCircle() {}
	FloatCircle(Vector2 origin, float size, float startRadian = 0, float endRadian = 3.141592)
		: origin(origin), size(size), startRadian(startRadian), endRadian(endRadian) {}

	bool intersect(FloatRect rc);
	bool isCollisionX(float x, Vector2 rangeY);
	bool isCollisionY(float y, Vector2 rangeX);
	bool isInsideRadian(float radian);
	bool isInsideRadian(float radian, Vector2 radianRange);
	bool isIntersectRadian(Vector2 rangeRadian);

	void render(bool useCamera);
};

