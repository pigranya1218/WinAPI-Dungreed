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
	void isCollisionX(float x, Vector2 rangeY, vector<float>& intersects);
	void isCollisionY(float y, Vector2 rangeX, vector<float>& intersects);
	bool isInsideRadian(float radian);
	bool isInsideRadian(float radian, Vector2 radianRange);
	bool isIntersectRadian(Vector2 rangeRadian);
	bool ptInCircle(POINT pt) const;
	
	float getRadian(float start, float end);

	void render(bool useCamera);
};

