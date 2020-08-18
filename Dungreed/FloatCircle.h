#pragma once
class FloatCircle
{
public:
	Vector2 origin; // 원점
	float size; // 반지름 사이즈
	float startRadian; // 중심으로부터 이루는 시작 각도 (이를 통해 호를 지원함)
	float endRadian; // 중심으로부터 이루는 종료 각도 (이를 통해 호를 지원함)

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

